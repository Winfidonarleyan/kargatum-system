/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "../Kargatum-lib/KargatumLoadSystem.h"
#include "../Kargatum-lib/KargatumScripts.h"
#include "ScriptMgr.h"
#include "DatabaseEnv.h"
#include "Chat.h"
#include "Player.h"

class KargatumOnlineReward : public PlayerScript
{
public:
    KargatumOnlineReward() : PlayerScript("KargatumOnlineReward") {}

    void OnBeforeUpdate(Player* player, uint32 p_time) override
    {
        if (!CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
            return;

        TypeReward TR = TypeReward(CONF_INT(conf::ONLINE_REWARD_TYPE));

        UpdateTimer.Update(p_time);

        if (UpdateTimer.Passed())
        {
            switch (TR)
            {
            case DEFAULT_REWARD:
                this->RewardDefault(player);
                break;
            case REWARD_PER_HOUR:
                this->RewardPerHour(player);
                break;
            default:
                break;
            }           

            UpdateTimer.Reset();
        }
    }

    void RewardDefault(Player* player)
    {
        ChatHandler handler(player->GetSession());
        uint32 PlayedTimeSec = player->GetTotalPlayedTime();
        uint64 PlayerGuid = player->GetGUID();

        KargatumLoad::RewardPlayedTimeContainer& sn = sKargatumLoad->GetRewardPlayedTime();
        for (auto itr : sn)
        {
            auto Seconds = itr.first;
            auto ItemID = itr.second.ItemID;
            auto Count = itr.second.Count;
            bool IsCompleteReward = false;

            std::string PlayedTimeSecStr = secsToTimeString(Seconds);

            if (IsRewardedPlayer(PlayerGuid, Seconds))
                continue;

            if (PlayedTimeSec > Seconds)
                IsCompleteReward = true;

            if (IsCompleteReward)
            {
#ifdef KARGATUM_RUS_LANG
                std::string Text = sKargatumScript->GetFormatString("Привет, %s!\nВы играете на нашем сервере уже более %s. Пожалуйста примите подарок", player->GetName().c_str(), PlayedTimeSecStr.c_str());
                sKargatumScript->SendMailPlayer(player, "Награда за онлайн на сервере", Text, ItemID, Count);
                handler.PSendSysMessage("Вы были вознаграждены за онлайн. Получить награду можно на почте.");
#else
                std::string Text = sKargatumScript->GetFormatString("Hi, %s!\nYou play on our server already more %s. Please accept gift", player->GetName().c_str(), PlayedTimeSecStr.c_str());
                sKargatumScript->SendMailPlayer(player, "Reward for online in world", Text, ItemID, Count);
                handler.PSendSysMessage("You were rewarded for online. You can get the award at the post office.");
#endif
                _lastrewardtimestore[PlayerGuid].push_back(Seconds);
            }
        }

        this->SaveRewardDB(player, true);
    }

    void RewardPerHour(Player* player)
    {
        ChatHandler handler(player->GetSession());
        uint32 PlayedTimeSec = player->GetTotalPlayedTime();
        uint64 PlayerGuid = player->GetGUID();
        uint32 ItemID = CONF_INT(conf::ONLINE_REWARD_TYPE_PER_HOUR_ITEMID);
        uint32 Count = CONF_INT(conf::ONLINE_REWARD_TYPE_PER_HOUR_ITEM_COUNT);
        uint32 TimeHour = HOUR;
        uint32 LastReward = _LastRewardTimePerHourStore[PlayerGuid];
        uint32 DiffTime = 0;

        while (DiffTime < PlayedTimeSec)
        {
            if (LastReward < DiffTime)
            {
                player->AddItem(ItemID, Count);
                _LastRewardTimePerHourStore[PlayerGuid] = DiffTime;
            }

            DiffTime += TimeHour;
        }

        this->SaveRewardDB(player, false);
    }

    void OnLogin(Player* player) override
    {
        if (!CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
            return;

        switch (CONF_INT(conf::ONLINE_REWARD_TYPE))
        {
        case DEFAULT_REWARD:
            this->LoadRewardFromDB(player, true);
            break;
        case REWARD_PER_HOUR:
            this->LoadRewardFromDB(player, false);
            break;
        default:
            break;
        }
    }

    void OnLogout(Player* player) override
    {
        if (!CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
            return;

        switch (CONF_INT(conf::ONLINE_REWARD_TYPE))
        {
        case DEFAULT_REWARD:
            _lastrewardtimestore.erase(player->GetGUID());
            break;
        case REWARD_PER_HOUR:
            _LastRewardTimePerHourStore.erase(player->GetGUID());
            break;
        default:
            break;
        }
    }

    void SaveRewardDB(Player* player, bool IsDefault)
    {
        uint64 PlayerGuid = player->GetGUID();

        if (IsDefault)
        {
            std::ostringstream ssRewarded;
            LastRewardTimeContainer::const_iterator itr = _lastrewardtimestore.find(PlayerGuid);
            if (itr != _lastrewardtimestore.end())
            {
                for (uint32 Rewarded : itr->second)
                    ssRewarded << Rewarded << ',';
            }

            std::string StrReward = ssRewarded.str();
            if (!StrReward.empty())
                StrReward.erase(StrReward.end() - 1, StrReward.end());

            if (StrReward.size() > 0)
                WorldDatabase.PExecute("UPDATE `online_reward_history` SET `Rewarded` = '%s' WHERE `PlayedGuid` = %u", StrReward.c_str(), PlayerGuid);
        }
        else
            if (_LastRewardTimePerHourStore[PlayerGuid])
                WorldDatabase.PExecute("UPDATE `online_reward_history` SET `RewardedPerHour` = %u WHERE `PlayedGuid` = %u", _LastRewardTimePerHourStore[PlayerGuid], PlayerGuid);
    }

    void LoadRewardFromDB(Player* player, bool IsDefault)
    {
        uint64 PlayerGuid = player->GetGUID();
        bool IsExistDB = true;

        QueryResult result = WorldDatabase.PQuery("SELECT * FROM `online_reward_history` WHERE `PlayedGuid` = %u", PlayerGuid);
        if (!result)
            IsExistDB = false;

        if (!IsExistDB)
            WorldDatabase.PExecute("INSERT INTO `online_reward_history`(`PlayedGuid`) VALUES (%u)", PlayerGuid);

        if (IsDefault && IsExistDB)
        {
            std::string ParamRewarded;

            QueryResult result = WorldDatabase.PQuery("SELECT Rewarded FROM `online_reward_history` WHERE `PlayedGuid` = %u", PlayerGuid);
            if (result)
                ParamRewarded = result->Fetch()->GetString();

            _lastrewardtimestore.erase(PlayerGuid);

            Tokenizer tokens(ParamRewarded, ',');
            for (uint8 i = 0; i < tokens.size(); )
                _lastrewardtimestore[PlayerGuid].push_back(atoi(tokens[i++]));
        }
        else if (!IsDefault && IsExistDB)
        {
            uint32 LasRewardPerHour = 0;

            QueryResult result = WorldDatabase.PQuery("SELECT RewardedPerHour FROM `online_reward_history` WHERE `PlayedGuid` = %u", PlayerGuid);
            if (result)
                LasRewardPerHour = result->Fetch()->GetUInt32();

            _LastRewardTimePerHourStore.erase(PlayerGuid);
            _LastRewardTimePerHourStore[PlayerGuid] = LasRewardPerHour;
        }
        else
            return;
    }

    bool IsRewardedPlayer(uint32 Guid, uint32 RewardSecond)
    {
        LastRewardTimeContainer::const_iterator itr = _lastrewardtimestore.find(Guid);
        if (itr != _lastrewardtimestore.end())
        {
            for (uint32 Rewarded : itr->second)
                if (Rewarded == RewardSecond)
                    return true;
        }

        return false;
    }

private:
    IntervalTimer& UpdateTimer = sKargatumConfig->GetUpdateTimerOnlineReward();

    typedef std::unordered_map<uint64, std::vector<uint32>> LastRewardTimeContainer;
    typedef std::unordered_map<uint64, uint32> LastRewardTimePerHourContainer;
    LastRewardTimePerHourContainer _LastRewardTimePerHourStore;
    LastRewardTimeContainer _lastrewardtimestore;
};

void AddSC_Kargatum_OnlineReward()
{
    new KargatumOnlineReward();
}
