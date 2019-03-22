/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "../Kargatum-lib/KargatumLoadSystem.h"
#include "../Kargatum-lib/KargatumScripts.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "LootMgr.h"

class KargatumLevelReward : public PlayerScript
{
public:
    KargatumLevelReward() : PlayerScript("KargatumLevelReward") { }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        if (!CONF_BOOL(conf::LEVEL_REWARD_ENABLE))
            return;

        uint8 PlayerLevel = player->getLevel();
        int32 Diff = PlayerLevel - oldLevel;

        if (Diff < 0 || PlayerLevel == 1 || PlayerLevel > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
            return;

        while (Diff)
        {
            RewardForLevel(player, PlayerLevel - Diff);
            Diff--;
        }
    }

private:
    LevelReward const* GetLevelReward(uint32 Level)
    {
        KargatumLoad::LevelRewardContainer& _store = sKargatumLoad->GetRewardLevel();
        KargatumLoad::LevelRewardContainer::const_iterator itr = _store.find(Level);
        if (itr != _store.end())
            return &(itr->second);

        return nullptr;
    }

    void RewardForLevel(Player* player, uint8 Level)
    {
        LevelReward const* levelReward = GetLevelReward(Level);
        if (!levelReward)
            return;

        ChatHandler handler(player->GetSession());

#ifdef KARGATUM_RUS_LANG
        handler.PSendSysMessage("Вы повысили уровень до %u и получаете награду!", Level);
#else
        handler.PSendSysMessage("You increased level to %u and get a reward!", Level);
#endif
        if (levelReward->Money)
        {
            player->ModifyMoney(levelReward->Money);

#ifdef KARGATUM_RUS_LANG
            handler.PSendSysMessage("Вы получили %s", sKargatumScript->GetMoneyString(levelReward->Money).c_str());
#else
            handler.PSendSysMessage("You get %s", sKargatumScript->GetMoneyString(levelReward->Money).c_str());
#endif
        }

        if (levelReward->ItemID && levelReward->ItemCount)
            player->AddItem(levelReward->ItemID, levelReward->ItemCount);
    }
};

void AddSC_Kargatum_LevelReward()
{
	new KargatumLevelReward();
}
