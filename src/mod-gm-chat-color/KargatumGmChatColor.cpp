/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "Player.h"
#include "Util.h"

class KargatumGmChatColor : public PlayerScript
{
public:
    KargatumGmChatColor() : PlayerScript("KargatumGmChatColor") { }

    void SetColorMessage(Player* player, std::string& Message)
    {
        if (!CONF_BOOL(conf::GM_CHAT_COLOR_ENABLE))
            return;

        if (player->isGMChat() && !Message.empty() && player->GetSession()->GetSecurity() >= 3)
            Message = CONF_STR(conf::GM_CHAT_COLOR_LEVEL_3) + Message;

        if (player->isGMChat() && !Message.empty() && player->GetSession()->GetSecurity() == 2)
            Message = CONF_STR(conf::GM_CHAT_COLOR_LEVEL_2) + Message;

        if (player->isGMChat() && !Message.empty() && player->GetSession()->GetSecurity() == 1)
            Message = CONF_STR(conf::GM_CHAT_COLOR_LEVEL_1) + Message;
    };

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Player* /*receiver*/) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Group* /*group*/) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Guild* /*guild*/) override
    {
        SetColorMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* /*channel*/) override
    {
        SetColorMessage(player, msg);
    }
};

void AddSC_Kargatum_GMChatColor()
{
    new KargatumGmChatColor();
}
