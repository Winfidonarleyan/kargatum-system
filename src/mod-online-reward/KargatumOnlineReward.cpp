/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifdef KARGATUMCORE
#include "KargatumConfig.h"
#include "KargatumLoadSystem.h"
#include "KargatumScript.h"
#else
#include "../Kargatum-lib/LibKargatumConfig.h"
#include "../Kargatum-lib/LibKargatumLoadSystem.h"
#include "../Kargatum-lib/LibKargatumScripts.h"
#endif

#include "ScriptMgr.h"
#include "DatabaseEnv.h"
#include "Chat.h"
#include "Player.h"

#ifdef KARGATUMCORE
#define MODULE_DB KargatumDatabase
#else
#define MODULE_DB WorldDatabase
#endif

class KargatumOnlineReward : public PlayerScript
{
public:
    KargatumOnlineReward() : PlayerScript("KargatumOnlineReward") {}

    void OnBeforeUpdate(Player* player, uint32 p_time) override
    {
        if (!CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
            return;

        UpdateTimer.Update(p_time);

        if (UpdateTimer.Passed())
        {
            if (CONF_BOOL(conf::ONLINE_REWARD_PER_ONLINE_ENABLE))
                this->RewardPerOnline(player);

            if (CONF_BOOL(conf::ONLINE_REWARD_PER_TIME_ENABLE))
                this->RewardPerTime(player);

            UpdateTimer.Reset();
        }
    }

    void OnLogin(Player* player) override
    {
        if (!CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
            return;

        if (CONF_BOOL(conf::ONLINE_REWARD_PER_ONLINE_ENABLE))
            this->LoadRewardFromDB(player, true);

        if (CONF_BOOL(conf::ONLINE_REWARD_PER_TIME_ENABLE))
            this->LoadRewardFromDB(player, false);
    }

    void OnLogout(Player* player) override
    {
        if (!CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
            return;

        if (CONF_BOOL(conf::ONLINE_REWARD_PER_ONLINE_ENABLE))
            _lastrewardtimestore.erase(player->GetGUID());

        if (CONF_BOOL(conf::ONLINE_REWARD_PER_TIME_ENABLE))
            _LastRewardTimePerTimeStore.erase(player->GetGUID());
    }
private:
    void RewardPerOnline(Player* player)
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

            if (IsRewardedPlayer(PlayerGuid, Seconds))
                continue;

            if (PlayedTimeSec > Seconds)
                IsCompleteReward = true;

            if (IsCompleteReward)
            {
                ChatHandler handler(player->GetSession());
                std::string Subject, Text, SelfMessage;
                std::string PlayedTimeSecStr = secsToTimeString(Seconds);

                KargatumMailVector ListItemPairs;
                ListItemPairs.push_back(KargatumMailItemPair(ItemID, Count));

#ifdef KARGATUM_RUS_LANG
                Subject = sKargatumScript->GetFormatString("Награда за онлайн %s", PlayedTimeSecStr.c_str());
                Text = sKargatumScript->GetFormatString("Привет, %s!\nВы играете на нашем сервере уже более %s. Пожалуйста примите подарок", player->GetName().c_str(), PlayedTimeSecStr.c_str());
                SelfMessage = sKargatumScript->GetFormatString("Вы были вознаграждены за онлайн (%s). Получить награду можно на почте.", PlayedTimeSecStr.c_str());
#else
                Subject = sKargatumScript->GetFormatString("Reward for online %s", PlayedTimeSecStr.c_str());
                Text = sKargatumScript->GetFormatString("Привет, %s!\nВы играете на нашем сервере уже более %s. Пожалуйста примите подарок", player->GetName().c_str(), PlayedTimeSecStr.c_str());
                SelfMessage = sKargatumScript->GetFormatString("You were rewarded for online (%s). You can get the award at the post office.", PlayedTimeSecStr.c_str());
#endif
                handler.PSendSysMessage("%s", SelfMessage.c_str());
                sKargatumScript->SendMoreItemsMail(player, Subject, Text, 0, ListItemPairs);

                _lastrewardtimestore[PlayerGuid].push_back(Seconds);
            }
        }

        this->SaveRewardDB(player, true);
    }

    void RewardPerTime(Player* player)
    {
        ChatHandler handler(player->GetSession());
        uint32 PlayedTimeSec = player->GetTotalPlayedTime();
        uint64 PlayerGuid = player->GetGUID();
        uint32 ItemID = CONF_INT(conf::ONLINE_REWARD_TYPE_PER_HOUR_ITEMID);
        uint32 Count = CONF_INT(conf::ONLINE_REWARD_TYPE_PER_HOUR_ITEM_COUNT);
        uint32 ConfPerTime = CONF_INT(conf::ONLINE_REWARD_PER_TIME_TIME);
        uint32 LastReward = _LastRewardTimePerTimeStore[PlayerGuid];
        uint32 DiffTime = 0;

        while (DiffTime < PlayedTimeSec)
        {
            if (LastReward < DiffTime)
            {
                ChatHandler handler(player->GetSession());
                std::string Subject, Text, SelfMessage;
                std::string PlayedTimeSecStr = secsToTimeString(DiffTime);

                KargatumMailVector ListItemPairs;
                ListItemPairs.push_back(KargatumMailItemPair(ItemID, Count));

#ifdef KARGATUM_RUS_LANG
                Subject = sKargatumScript->GetFormatString("Награда за онлайн %s", PlayedTimeSecStr.c_str());
                Text = sKargatumScript->GetFormatString("Привет, %s!\nВы играете на нашем сервере уже более %s. Пожалуйста примите подарок", player->GetName().c_str(), PlayedTimeSecStr.c_str());
                SelfMessage = sKargatumScript->GetFormatString("Вы были вознаграждены за онлайн (%s). Получить награду можно на почте.", PlayedTimeSecStr.c_str());
#else
                Subject = sKargatumScript->GetFormatString("Reward for online %s", PlayedTimeSecStr.c_str());
                Text = sKargatumScript->GetFormatString("Привет, %s!\nВы играете на нашем сервере уже более %s. Пожалуйста примите подарок", player->GetName().c_str(), PlayedTimeSecStr.c_str());
                SelfMessage = sKargatumScript->GetFormatString("You were rewarded for online (%s). You can get the award at the post office.", PlayedTimeSecStr.c_str());
#endif
                handler.PSendSysMessage("%s", SelfMessage.c_str());
                sKargatumScript->SendMoreItemsMail(player, Subject, Text, 0, ListItemPairs);

                _LastRewardTimePerTimeStore[PlayerGuid] = DiffTime;
            }

            DiffTime += ConfPerTime;
        }

        this->SaveRewardDB(player, false);
    }

    void SaveRewardDB(Player* player, bool IsPerOnline)
    {
        uint64 PlayerGuid = player->GetGUID();

        if (IsPerOnline)
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
                MODULE_DB.PExecute("UPDATE `online_reward_history` SET `Rewarded` = '%s' WHERE `PlayedGuid` = %u", StrReward.c_str(), PlayerGuid);
        }
        else
            if (_LastRewardTimePerTimeStore[PlayerGuid])
                MODULE_DB.PExecute("UPDATE `online_reward_history` SET `RewardedPerHour` = %u WHERE `PlayedGuid` = %u", _LastRewardTimePerTimeStore[PlayerGuid], PlayerGuid);
    }

    void LoadRewardFromDB(Player* player, bool IsPerOnline)
    {
        uint64 PlayerGuid = player->GetGUID();
        bool IsExistDB = true;

        QueryResult result = MODULE_DB.PQuery("SELECT * FROM `online_reward_history` WHERE `PlayedGuid` = %u", PlayerGuid);
        if (!result)
            IsExistDB = false;

        if (!IsExistDB)
            MODULE_DB.PExecute("INSERT INTO `online_reward_history`(`PlayedGuid`) VALUES (%u)", PlayerGuid);

        if (IsPerOnline && IsExistDB)
        {
            std::string ParamRewarded;

            QueryResult result = MODULE_DB.PQuery("SELECT Rewarded FROM `online_reward_history` WHERE `PlayedGuid` = %u", PlayerGuid);
            if (result)
                ParamRewarded = result->Fetch()->GetString();

            _lastrewardtimestore.erase(PlayerGuid);

            Tokenizer tokens(ParamRewarded, ',');
            for (uint8 i = 0; i < tokens.size(); )
                _lastrewardtimestore[PlayerGuid].push_back(atoi(tokens[i++]));
        }
        else if (!IsPerOnline && IsExistDB)
        {
            uint32 LasRewardPerHour = 0;

            QueryResult result = MODULE_DB.PQuery("SELECT RewardedPerHour FROM `online_reward_history` WHERE `PlayedGuid` = %u", PlayerGuid);
            if (result)
                LasRewardPerHour = result->Fetch()->GetUInt32();

            _LastRewardTimePerTimeStore.erase(PlayerGuid);
            _LastRewardTimePerTimeStore[PlayerGuid] = LasRewardPerHour;
        }
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

    IntervalTimer& UpdateTimer = sKargatumConfig->GetUpdateTimerOnlineReward();

    typedef std::unordered_map<uint64, std::vector<uint32>> LastRewardTimeContainer;
    typedef std::unordered_map<uint64, uint32> LastRewardTimePerHourContainer;
    LastRewardTimePerHourContainer _LastRewardTimePerTimeStore;
    LastRewardTimeContainer _lastrewardtimestore;
};

void AddSC_Kargatum_OnlineReward()
{
    new KargatumOnlineReward();
}
