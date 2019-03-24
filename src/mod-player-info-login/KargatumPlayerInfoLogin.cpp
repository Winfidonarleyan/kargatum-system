/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
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
#ifdef KARGATUM_RUS_LANG
        handler.PSendSysMessage("|cffff0000# |cff00ff00Привет,|r %s", PlayerName.c_str());

        if (GMLevel)
            handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш уровень доступа:|r %u", GMLevel);

        handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш IP:|r %s", PlayerIP.c_str());
        handler.PSendSysMessage("|cffff0000# |cff00ff00Сейчас|r %u |cff00ff00игроков онлайн|r |cff00ff00(максимум:|r %u|cff00ff00)|r", PlayerOnlineCount, connPeak);
        handler.PSendSysMessage("|cffff0000# |cff00ff00Время работы сервера:|r %s", ServerUptime.c_str());
#else
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
