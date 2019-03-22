/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "KargatumConfig.h"
#include "KargatumLoadSystem.h"
#include "Config.h"
#include "Log.h"
#include "ScriptMgr.h"

KargatumConfig* KargatumConfig::instance()
{
    static KargatumConfig instance;
    return &instance;
}

void KargatumConfig::LoadConfig()
{
#ifdef KARGATUM_RUS_LANG
    sLog->outString("Загрузка кастомной конфигурации");
#else
    sLog->outString("Loading custom configuration");
#endif
    
    // mod-anti-advertisment
    m_bool[conf::ANTIAD_ENABLE]					                = sConfigMgr->GetBoolDefault("AntiAD.Enable", true);
	m_bool[conf::ANTIAD_MSG_GM_WORLD_ENABLE]	                = sConfigMgr->GetBoolDefault("AntiAD.Message.GM.World.Enable", true);
	m_bool[conf::ANTIAD_FULLMSG_GM_WORLD_ENABLE]                = sConfigMgr->GetBoolDefault("AntiAD.FullMessage.GM.World.Enable", true);
	m_bool[conf::ANTIAD_MSG_SELF_ENABLE]		                = sConfigMgr->GetBoolDefault("AntiAD.Message.Self.Enable", true);
	m_bool[conf::ANTIAD_MUTE_ENABLE]			                = sConfigMgr->GetBoolDefault("AntiAD.Enable.Mute", true);
	m_bool[conf::ANTIAD_MUTE_GM_ENABLE]			                = sConfigMgr->GetBoolDefault("AntiAD.Mute.GM", true);
	m_int[conf::ANTIAD_MUTETIME]				                = sConfigMgr->GetIntDefault("AntiAD.Mutetime", 0);
    
    // mod-auto-revive
    m_bool[conf::AUTO_REVIVE_ENABLE]                            = sConfigMgr->GetBoolDefault("AutoRevive.Enable", false);
    m_int[conf::AUTO_REVIVE_ZONE_ID]                            = sConfigMgr->GetIntDefault("AutoRevive.ZoneID", 0);

    // mod-bg-reward
    m_bool[conf::BG_REWARD_ENABLE]                              = sConfigMgr->GetBoolDefault("BG.Reward.Enable", true);
    m_int[conf::BG_REWARD_ITEMID_WSG]                           = sConfigMgr->GetIntDefault("BG.Reward.ItemID.WSG", 20558);
    m_int[conf::BG_REWARD_ITEMID_ARATHI]                        = sConfigMgr->GetIntDefault("BG.Reward.ItemID.Arathi", 20559);
    m_int[conf::BG_REWARD_ITEMID_ALTERAC]                       = sConfigMgr->GetIntDefault("BG.Reward.ItemID.Alterac", 20560);
    m_int[conf::BG_REWARD_ITEMID_ISLE]                          = sConfigMgr->GetIntDefault("BG.Reward.ItemID.Isle", 47395);
    m_int[conf::BG_REWARD_ITEMID_ANCIENTS]                      = sConfigMgr->GetIntDefault("BG.Reward.ItemID.Ancients", 42425);
    m_int[conf::BG_REWARD_ITEMID_EYE]                           = sConfigMgr->GetIntDefault("BG.Reward.ItemID.Eye", 29024);
    m_int[conf::BG_REWARD_WIN_TEAM_ITEM_COUNT]                  = sConfigMgr->GetIntDefault("BG.Reward.WinnerTeam.Count", 3);
    m_int[conf::BG_REWARD_LOS_TEAM_ITEM_COUNT]                  = sConfigMgr->GetIntDefault("BG.Reward.LoserTeam.Count", 1);

    // mod-buff-command
    m_bool[conf::BUFF_COMMAND_ENABLE]                           = sConfigMgr->GetBoolDefault("Buff.Command.Enable", true);
    
    // mod-faction-icons-channel
    m_bool[conf::CHANNEL_ICON_FACTION_ENABLE]                   = sConfigMgr->GetBoolDefault("Channel.Icon.Faction.Enable", true);
    m_bool[conf::CHANNEL_ICON_FACTION_ONLYLFG]		            = sConfigMgr->GetBoolDefault("Channel.Icon.Faction.OnlyLFG", true);
    m_bool[conf::CHANNEL_ICON_FACTION_GM_ENABLE]		        = sConfigMgr->GetBoolDefault("Channel.Icon.Faction.GM", true); 

    // mod-gm-chat-color
    m_bool[conf::GM_CHAT_COLOR_ENABLE]                          = sConfigMgr->GetBoolDefault("GM.Chat.Color.Enable", false);
    m_string[conf::GM_CHAT_COLOR_LEVEL_3]                       = sConfigMgr->GetStringDefault("GM.Chat.Color.Level.3", "");
    m_string[conf::GM_CHAT_COLOR_LEVEL_2]                       = sConfigMgr->GetStringDefault("GM.Chat.Color.Level.2", "");
    m_string[conf::GM_CHAT_COLOR_LEVEL_1]                       = sConfigMgr->GetStringDefault("GM.Chat.Color.Level.1", "");
    
    // mod-level-reward
    m_bool[conf::LEVEL_REWARD_ENABLE]                           = sConfigMgr->GetBoolDefault("Level.Reward.Enable", false);
    
    // mod-notify-muted
    m_bool[conf::MSG_NOT_CAN_SPEAK_ENABLE]		                = sConfigMgr->GetBoolDefault("NotCanSpeak.Msg.Enable", true);

    // mod-online-reward
    m_bool[conf::ONLINE_REWARD_ENABLE]                          = sConfigMgr->GetBoolDefault("Online.Reward.Enable", true);
    m_int[conf::ONLINE_REWARD_TYPE]                             = sConfigMgr->GetIntDefault("Online.Reward.Type", 0);
    m_int[conf::ONLINE_REWARD_TYPE_PER_HOUR_ITEMID]             = sConfigMgr->GetIntDefault("Online.Reward.Type.Per.Hour.ItemID", 40265);
    m_int[conf::ONLINE_REWARD_TYPE_PER_HOUR_ITEM_COUNT]         = sConfigMgr->GetIntDefault("Online.Reward.Type.Per.Hour.Item.Count", 1);
    m_int[conf::ONLINE_REWARD_TIME_CHECK]                       = sConfigMgr->GetIntDefault("Online.Reward.Time.Check", 60000);

    // mod-player-login
    m_bool[conf::PLAYER_INFO_LOGIN_ENABLE]                      = sConfigMgr->GetBoolDefault("Player.Info.Login.Enable", true);

    // mod-spell-duration
    m_bool[conf::SPELL_DURATION_ENABLE]                         = sConfigMgr->GetBoolDefault("Spell.Duration.Enable", true);

#ifdef KARGATUM_RUS_LANG
    sLog->outString(">> Загрузка кастомной конфигурации завершена");
#else
    sLog->outString(">> Loading custom configuration done");
#endif

    this->CheckConfigOption();
    this->SetTimers();
}

void KargatumConfig::CheckConfigOption()
{
    sLog->outString();
    
#ifdef KARGATUM_RUS_LANG
    sLog->outString("Началась проверка кастомной конфигурации...");
#else
    sLog->outString("Start check custom configuration");
#endif

    if (m_int[conf::ONLINE_REWARD_TIME_CHECK] < 5 * IN_MILLISECONDS)
    {
#ifdef KARGATUM_RUS_LANG
        sLog->outString("-> Время для проверки награды очень мало (%u секунд). Установлено по умолчанию 60 секунд.", m_int[conf::ONLINE_REWARD_TIME_CHECK]);
#else
        sLog->outString("-> Time for check reward very small (%u secs). Set 60 sec.", m_int[conf::ONLINE_REWARD_TIME_CHECK]);
#endif        
        m_int[conf::ONLINE_REWARD_TIME_CHECK] = 60 * IN_MILLISECONDS;
    }
    
#ifdef KARGATUM_RUS_LANG
    sLog->outString(">> Проверка кастомной конфигурации завершена");
#else
    sLog->outString(">> Check custom configuration done");
#endif
}

void KargatumConfig::SetTimers()
{
    _UpdateTimerOnlineReward.SetInterval(m_int[conf::ONLINE_REWARD_TIME_CHECK] * IN_MILLISECONDS);
}

class KargatumStartSystem : public WorldScript
{
public:
    KargatumStartSystem() : WorldScript("KargatumStartSystem") { }

    void OnStartup() override
    {
        sKargatumLoad->LoadKargatumSystem();
    }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        sKargatumConfig->LoadConfig();
    }
};

void AddSC_Kargatum_Startup()
{
    new KargatumStartSystem();
}


