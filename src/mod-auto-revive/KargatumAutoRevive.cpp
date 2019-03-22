/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Player.h"
#include "Common.h"

class KargatumAutoRevive : public PlayerScript
{
public:
    KargatumAutoRevive() : PlayerScript("KargatumAutoRevive") {}

	void OnBeforeUpdate(Player* player, uint32 diff) override
	{
		if (!CONF_BOOL(conf::AUTO_REVIVE_ENABLE))
			return;

        if (AccountMgr::IsPlayerAccount(player->GetSession()->GetSecurity()))
            return;

		uint32 NowHealth = player->GetHealth();
		uint32 TimeCheck = 1000;
		uint32 configZoneID = CONF_INT(conf::AUTO_REVIVE_ZONE_ID);
		uint32 zoneID = player->GetZoneId();

		if (TimeCheck_AutoRevive < diff)
		{
			if (NowHealth <= 1)
			{
				if (configZoneID)
				{
					if (configZoneID == zoneID)
					{
						player->ResurrectPlayer(1.0f);
						player->SaveToDB(false, false);
					}
				}
				else
				{
					player->ResurrectPlayer(1.0f);
					player->SaveToDB(false, false);
				}
			}
			
			TimeCheck_AutoRevive = TimeCheck;
		}
		else
			TimeCheck_AutoRevive -= diff;
	}

private:
	uint32 TimeCheck_AutoRevive = 0;
};

void AddSC_Kargatum_Auto_Revive()
{
    new KargatumAutoRevive();
}
