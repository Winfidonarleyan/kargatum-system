/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "../Kargatum-lib/KargatumLoadSystem.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Player.h"
#include "Chat.h"
#include <vector>

class KargatumBuffCommand : public CommandScript
{
public:
    KargatumBuffCommand() : CommandScript("KargatumBuffCommand") {}

	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> commandTable = // .commands
		{
			{ "buff",				SEC_PLAYER,			false, &HandleBuffCommand,	""}
		};

		return commandTable;
	}

	static bool HandleBuffCommand(ChatHandler *handler, const char *args)
	{
        if (!CONF_BOOL(conf::BUFF_COMMAND_ENABLE))
        {
#ifdef KARGATUM_RUS_LANG
			handler->SendSysMessage("Команда отключена");
#else
			handler->SendSysMessage("Modules 'mod-player-buff' is disabled");
#endif
			handler->SetSentErrorMessage(true);
            return false;
        }

        Player* player = handler->GetSession()->GetPlayer();
		std::string ArgStr = (char*)args;

		if (ArgStr == "reload" && !AccountMgr::IsAdminAccount(player->GetSession()->GetSecurity()))
		{
#ifdef KARGATUM_RUS_LANG
			sLog->outString("Перезагрузка баффов для команды .buff...");
			sKargatumLoad->LoadBuffData();
			handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `player_buff` |cFFFF0000перезагружена.|r");
#else
			sLog->outString("Re-Loading Player Buff data...");
			sKargatumLoad->LoadBuffData();
			handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 DB Table|r `player_buff` |cFFFF0000reloaded.|r");
#endif
			return true;
		}
		else
		{
			if (player->duel || player->GetMap()->IsBattleArena() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead(), player->IsInCombat() || player->IsInFlight())
			{
#ifdef KARGATUM_RUS_LANG
				handler->SendSysMessage("Сейчас вы не можете этого сделать");
#else
				handler->SendSysMessage("You can not do it now");
#endif				
				handler->SetSentErrorMessage(true);
				return false;
			}

			player->RemoveAurasByType(SPELL_AURA_MOUNTED);

			KargatumLoad::BuffDataContainer& buffStore = sKargatumLoad->GetBuffData();
			for (auto i : buffStore)
				player->CastSpell(player, i, true);

			return true;
		}
	}
};

void AddSC_Kargatum_BuffCommand()
{
	new KargatumBuffCommand();
}
