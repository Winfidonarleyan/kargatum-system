/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

#ifdef KARGATUMCORE
#include "KargatumConfig.h"
#include "KargatumLoadSystem.h"
#include "KargatumLanguage.h"
#else
#include "../Kargatum-lib/LibKargatumConfig.h"
#include "../Kargatum-lib/LibKargatumLoadSystem.h"
#include "../Kargatum-lib/LibKargatumLanguage.h"
#endif

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "Player.h"

class Kargatum_AntiAdvertisment : public PlayerScript
{
public:
    Kargatum_AntiAdvertisment() : PlayerScript("Kargatum_AntiAdvertisment") { }

    void Mute(Player* player)
    {
        if (!CONF_BOOL(conf::ANTIAD_MUTE_ENABLE))
            return;

        if (!CONF_BOOL(conf::ANTIAD_MUTE_GM_ENABLE) && !AccountMgr::IsPlayerAccount(player->GetSession()->GetSecurity()))
            return;

        ChatHandler handler(player->GetSession());
        std::string NameLink = handler.GetNameLink(player);

        player->GetSession()->m_muteTime = time(nullptr) + CONF_INT(conf::ANTIAD_MUTETIME) * MINUTE;

        if (CONF_BOOL(conf::ANTIAD_MSG_SELF_ENABLE))
            handler.PSendSysMessage(lang::ANTIAD_SEND_SELF, CONF_INT(conf::ANTIAD_MUTETIME));
    }

    void SendGMTexts(std::string NameLink, std::string ADMessage, std::string FullMessage)
    {
        if (CONF_BOOL(conf::ANTIAD_MSG_GM_WORLD_ENABLE))
            sWorld->SendGMText(lang::ANTIAD_SEND_GM_TEXT, NameLink.c_str(), ADMessage.c_str());

        if (CONF_BOOL(conf::ANTIAD_FULLMSG_GM_WORLD_ENABLE))
            sWorld->SendGMText(lang::ANTIAD_SEND_GM_TEXT_FULL, NameLink.c_str(), FullMessage.c_str());
    }

    void CheckMessage(Player* player, std::string& msg)
    {
        if (!CONF_BOOL(conf::ANTIAD_ENABLE))
            return;

        KargatumLoad::ChatMuteContainer& store = sKargatumLoad->GetAntiADMesages();
        std::string CheckMsg = msg;
        std::string FullMessage = msg;
        CheckMsg.erase(remove_if(CheckMsg.begin(), CheckMsg.end(), ::isspace), CheckMsg.end());
        std::transform(CheckMsg.begin(), CheckMsg.end(), CheckMsg.begin(), ::tolower);

        ChatHandler handler(player->GetSession());
        std::string NameLink = handler.GetNameLink(player);

        for (auto ADMessage : store)
        {
            if (CheckMsg.find(ADMessage) != std::string::npos)
            {
                msg = "";
                SendGMTexts(NameLink, ADMessage, FullMessage);
                Mute(player);
            }
        }
    };

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg) override
    {
        CheckMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Player* /*receiver*/) override
    {
        CheckMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Group* /*group*/) override
    {
        CheckMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Guild* /*guild*/) override
    {
        CheckMessage(player, msg);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* /*channel*/) override
    {
        CheckMessage(player, msg);
    }
};

void AddSC_Kargatum_AntiAdvertisment()
{
    new Kargatum_AntiAdvertisment();
}
