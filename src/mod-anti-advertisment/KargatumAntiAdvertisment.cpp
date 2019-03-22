/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/KargatumConfig.h"
#include "../Kargatum-lib/KargatumLoadSystem.h"
#include "../Kargatum-lib/KargatumLanguage.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "Player.h"

class Kargatum_AntiAdvertisment : public PlayerScript
{
public:
    Kargatum_AntiAdvertisment() : PlayerScript("Kargatum_AntiAdvertisment") { }

    void CheckMessage(Player* player, std::string& msg)
    {
        if (!CONF_BOOL(conf::ANTIAD_ENABLE))
            return;

        KargatumLoad::ChatMuteContainer& store = sKargatumLoad->GetAntiADMesages();
        std::string CheckMsg = msg;
        std::string FullMsg = msg;
        CheckMsg.erase(remove_if(CheckMsg.begin(), CheckMsg.end(), ::isspace), CheckMsg.end());
        std::transform(CheckMsg.begin(), CheckMsg.end(), CheckMsg.begin(), ::tolower);

        ChatHandler handler(player->GetSession());
        std::string NameLink = handler.GetNameLink(player);
        uint32 ConfMuteTime = CONF_INT(conf::ANTIAD_MUTETIME);

        for (auto MessageAd : store)
        {
            if (CheckMsg.find(MessageAd) != std::string::npos)
            {
                msg = "";                
                int64 muteTime = time(nullptr) + ConfMuteTime * MINUTE;

                if (CONF_BOOL(conf::ANTIAD_MSG_GM_WORLD_ENABLE))
                    sWorld->SendGMText(lang::ANTIAD_SEND_GM_TEXT, NameLink.c_str(), MessageAd.c_str());

                if (CONF_BOOL(conf::ANTIAD_FULLMSG_GM_WORLD_ENABLE))
                    sWorld->SendGMText(lang::ANTIAD_SEND_GM_TEXT_FULL, NameLink.c_str(), FullMsg.c_str());

                if (CONF_BOOL(conf::ANTIAD_MUTE_ENABLE))
                {
                    if (CONF_BOOL(conf::ANTIAD_MUTE_GM_ENABLE) && !AccountMgr::IsPlayerAccount(player->GetSession()->GetSecurity()))
                        player->GetSession()->m_muteTime = muteTime;

                    if (CONF_BOOL(conf::ANTIAD_MSG_SELF_ENABLE))
                        handler.PSendSysMessage(lang::ANTIAD_SEND_SELF, ConfMuteTime);
                }
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
