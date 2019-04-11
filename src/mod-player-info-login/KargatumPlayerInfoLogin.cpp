/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

#ifdef KARGATUMCORE
#include "KargatumConfig.h"
#include "KargatumVIP.h"
#include "KargatumScript.h"
#else
#include "../Kargatum-lib/LibKargatumConfig.h"
#endif

#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"

class KargatumPlayerInfoLogin : public PlayerScript
{
public:
    KargatumPlayerInfoLogin() : PlayerScript("KargatumPlayerInfoLogin") {}

    void OnLogin(Player* player) override
    {
        if (!CONF_BOOL(conf::PLAYER_INFO_LOGIN_ENABLE))
            return;
        
        ChatHandler handler(player->GetSession());

        std::string NameLink            = handler.GetNameLink(player);
        std::string PlayerName          = player->GetName();
        uint32 PlayerOnlineCount        = sWorld->GetPlayerCount();
        std::string ServerUptime        = secsToTimeString(sWorld->GetUptime());
        std::string PlayerIP            = player->GetSession()->GetRemoteAddress();
        uint32 GMLevel                  = player->GetSession()->GetSecurity();
        uint32 connPeak                 = sWorld->GetMaxActiveSessionCount();

        handler.PSendSysMessage("|cffff0000##############################|r");
#ifdef KARGATUMCORE
        uint32 AccountID    = player->GetSession()->GetAccountId();
        std::string GMlevel = sKargatumScript->GetGMLevelString(player->GetSession());
        uint32 OpenTickets  = sKargatumScript->GetOpenTicket();

        handler.PSendSysMessage("|cffff0000# |cff00ff00Привет,|r %s", PlayerName.c_str());

        if (player->GetSession()->GetSecurity() >= SEC_MODERATOR)
            handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш уровень доступа:|r %s", GMlevel.c_str());

        handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш IP:|r %s", PlayerIP.c_str());
        handler.PSendSysMessage("|cffff0000# |cff00ff00Сейчас|r %u |cff00ff00игроков онлайн|r |cff00ff00(максимум:|r %u|cff00ff00)|r", PlayerOnlineCount, connPeak);
        handler.PSendSysMessage("|cffff0000# |cff00ff00Время работы сервера:|r %s", ServerUptime.c_str());

        if (player->GetSession()->GetSecurity() >= SEC_MODERATOR)
            handler.PSendSysMessage("|cffff0000# |cff00ff00Открытые тикеты:|r %u", OpenTickets);

        if (player->GetSession()->IsVIP())
        {
            uint32 unsetdate = kVIP->GetUnSetDate(AccountID);
            std::string timeStr = secsToTimeString(unsetdate - time(nullptr), false, false);

            handler.PSendSysMessage("|cffff0000#|cff00ff00 Статус премиум аккаунта:|r |cff14ECCFИмеет премиум доступ");
            handler.PSendSysMessage("|cFFFF0000# |cff00ff00Премиум аккаунт закончится через|r %s", timeStr.c_str());
        }
        else
            handler.PSendSysMessage("|cffff0000#|cff00ff00 Статус премиум аккаунта:|r |cff14ECCFНе имеет премиум доступа");
#endif

#if KARGATUM_RUS_LANG && !KARGATUMCORE
        handler.PSendSysMessage("|cffff0000# |cff00ff00Привет,|r %s", PlayerName.c_str());

        if (GMLevel)
            handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш уровень доступа:|r %u", GMLevel);

        handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш IP:|r %s", PlayerIP.c_str());
        handler.PSendSysMessage("|cffff0000# |cff00ff00Сейчас|r %u |cff00ff00игроков онлайн|r |cff00ff00(максимум:|r %u|cff00ff00)|r", PlayerOnlineCount, connPeak);
        handler.PSendSysMessage("|cffff0000# |cff00ff00Время работы сервера:|r %s", ServerUptime.c_str());
#elif !KARGATUM_RUS_LANG && !KARGATUMCORE
        handler.PSendSysMessage("|cffff0000# |cff00ff00Hi,|r %s", PlayerName.c_str());

        if (GMLevel)
            handler.PSendSysMessage("|cffff0000# |cff00ff00You account level:|r %u", GMLevel);

        handler.PSendSysMessage("|cffff0000# |cff00ff00You IP:|r %s", PlayerIP.c_str());
        handler.PSendSysMessage("|cffff0000# |cff00ff00Now|r %u |cff00ff00player online|r |cff00ff00(max:|r %u|cff00ff00)|r", PlayerOnlineCount, connPeak);
        handler.PSendSysMessage("|cffff0000# |cff00ff00Server uptime:|r %s", ServerUptime.c_str());
#endif
        handler.PSendSysMessage("|cffff0000##############################|r");
    }
};

void AddSC_Kargatum_PlayerLoginInfo()
{
    new KargatumPlayerInfoLogin();
}
