/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifdef KARGATUMCORE
#include "KargatumConfig.h"
#else
#include "../Kargatum-lib/LibKargatumConfig.h"
#endif

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "Channel.h"
#include "Player.h"

class KargatumIconsChannel : public PlayerScript
{
public:
    KargatumIconsChannel() : PlayerScript("KargatumIconsChannel") { }

	void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* channel) override
	{
		if (!CONF_BOOL(conf::CHANNEL_ICON_FACTION_ENABLE))
			return;

        if (!player || !channel)
            return;

		if (CONF_BOOL(conf::CHANNEL_ICON_FACTION_ONLYLFG) && !channel->IsLFG())
			return;

		if (!CONF_BOOL(conf::CHANNEL_ICON_FACTION_GM_ENABLE) && !AccountMgr::IsPlayerAccount(player->GetSession()->GetSecurity()))
			return;

        std::string IconHorge       = "|TInterface\\PVPFrame\\PVP-Currency-Horde:18:18:-3:-3|t";
        std::string IconAlliance    = "|TInterface\\PVPFrame\\PVP-Currency-Alliance:18:18:-3:-3|t";

		std::stringstream ssMsg;
		ssMsg << ((player->GetTeamId() == TEAM_HORDE) ? IconHorge : IconAlliance) << msg;
		msg = ssMsg.str();
	}
};

void AddSC_Kargatum_IconFaction()
{
	new KargatumIconsChannel();
}
