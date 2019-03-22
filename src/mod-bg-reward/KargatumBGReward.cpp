/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Battleground.h"

class KargatumRewardBattleground : public BGScript
{
public:
    KargatumRewardBattleground() : BGScript("KargatumRewardBattleground") {}

    void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId) override
    {
        if (!CONF_BOOL(conf::BG_REWARD_ENABLE))
            return;
            
        // Not reward on end arena
        if (bg->isArena())
            return;

        // Reward ItemID
        uint32 itemWSG       = CONF_INT(conf::BG_REWARD_ITEMID_WSG);
        uint32 itemARATHI    = CONF_INT(conf::BG_REWARD_ITEMID_ARATHI);
        uint32 itemALTERAC   = CONF_INT(conf::BG_REWARD_ITEMID_ALTERAC);
        uint32 itemISLE      = CONF_INT(conf::BG_REWARD_ITEMID_ISLE);
        uint32 itemANCIENT   = CONF_INT(conf::BG_REWARD_ITEMID_ANCIENTS);
        uint32 itemEYE       = CONF_INT(conf::BG_REWARD_ITEMID_EYE);

        // Reward Count
        uint32 WinnerCount  = CONF_INT(conf::BG_REWARD_WIN_TEAM_ITEM_COUNT);
        uint32 LoserCount   = CONF_INT(conf::BG_REWARD_LOS_TEAM_ITEM_COUNT);

        TeamId bgTeamId = player->GetBgTeamId();
        uint32 RewardCount = 0;

        bgTeamId == winnerTeamId ? (RewardCount = WinnerCount) : (RewardCount = LoserCount);

        switch (player->GetZoneId())
        {
        case 3277: // Warsong Gulch
            player->AddItem(itemWSG, RewardCount);
            break;
        case 3358: // Arathi Basin
            player->AddItem(itemARATHI, RewardCount);
            break;
        case 3820: // Eye of the Storm
            player->AddItem(itemEYE, RewardCount);
            break;
        case 4710: // Isle of Conquest
            player->AddItem(itemISLE, RewardCount);
            break;
        case 4384: // Strand of the Ancients
            player->AddItem(itemANCIENT, RewardCount);
            break;
        case 2597: // Alterac Valley
            player->AddItem(itemALTERAC, RewardCount);
            break;
        default:
            break;
        }
    }
};

void AddSC_Kargatum_BGReward()
{
	new KargatumRewardBattleground();
}
