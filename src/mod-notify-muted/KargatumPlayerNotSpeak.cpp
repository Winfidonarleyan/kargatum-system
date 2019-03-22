/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "../Kargatum-lib/KargatumLanguage.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"

class Kargatum_PlayerNotSpeak : public PlayerScript
{
public:
	Kargatum_PlayerNotSpeak() : PlayerScript("Kargatum_PlayerNotSpeak") {}

	void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Player* receiver) override
	{
		if (!CONF_BOOL(conf::MSG_NOT_CAN_SPEAK_ENABLE))
			return;

		if (receiver->CanSpeak())
			return;

		uint64 MuteTime = receiver->GetSession()->m_muteTime;

		if (MuteTime == 0)
			return;

		std::string MuteTimeStr = secsToTimeString(MuteTime - time(nullptr), true);
		std::string NameLink = ChatHandler(receiver->GetSession()).playerLink(receiver->GetName());

		ChatHandler(player->GetSession()).PSendSysMessage(lang::RECEIVER_NOT_SPEAK, NameLink.c_str(), MuteTimeStr.c_str());
	}
};

void AddSC_Kargatum_PlayerNotSpeak()
{
	new Kargatum_PlayerNotSpeak();
}
