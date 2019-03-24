/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef _KARGATUM_CONFIG_H
#define _KARGATUM_CONFIG_H

#include "Common.h"
#include "Timer.h"

// Удалите коментарий со следующей строки если хотите русский язык / Add comment for next line for english language
#define KARGATUM_RUS_LANG

namespace conf
{
	/// - Структуры конфига
	enum KargatumBoolConfigs
	{
		// mod-anti-advertisment
		ANTIAD_ENABLE,
		ANTIAD_MSG_GM_WORLD_ENABLE,
		ANTIAD_FULLMSG_GM_WORLD_ENABLE,
		ANTIAD_MSG_SELF_ENABLE,
		ANTIAD_MUTE_ENABLE,
		ANTIAD_MUTE_GM_ENABLE,		

		// mod-auto-revive
		AUTO_REVIVE_ENABLE,

		// mod-bg-reward
		BG_REWARD_ENABLE,

		// mod-buff-command
		BUFF_COMMAND_ENABLE,

		// mod-faction-icons-channel
		CHANNEL_ICON_FACTION_ENABLE,
		CHANNEL_ICON_FACTION_ONLYLFG,
		CHANNEL_ICON_FACTION_GM_ENABLE,

		// mod-gm-chat-color
		GM_CHAT_COLOR_ENABLE,
		
		// mod-level-reward
		LEVEL_REWARD_ENABLE,
		
		// mod-notify-muted
		MSG_NOT_CAN_SPEAK_ENABLE,

		// mod-online-reward
		ONLINE_REWARD_ENABLE,

		// mod-player-login
		PLAYER_INFO_LOGIN_ENABLE,

		// mod-spell-duration
		SPELL_DURATION_ENABLE,

		// Конец
		BOOL_VALUE_COUNT
	};

	enum KargatumFloatConfigs
	{
		TEST_CONF_FLOAT,

		// Конец
		FLOAT_VALUE_COUNT
	};

	enum KargatumIntConfigs
	{
        // mod-anti-advertisment
        ANTIAD_MUTETIME,

        // mod-auto-revive
		AUTO_REVIVE_ZONE_ID,		
		
		// mod-bg-reward
		BG_REWARD_ITEMID_WSG,
		BG_REWARD_ITEMID_ARATHI,
		BG_REWARD_ITEMID_ALTERAC,
		BG_REWARD_ITEMID_ISLE,
		BG_REWARD_ITEMID_ANCIENTS,
		BG_REWARD_ITEMID_EYE,
		BG_REWARD_WIN_TEAM_ITEM_COUNT,
		BG_REWARD_LOS_TEAM_ITEM_COUNT,

		// mod-online-reward
		ONLINE_REWARD_TYPE,
		ONLINE_REWARD_TYPE_PER_HOUR_ITEMID,
		ONLINE_REWARD_TYPE_PER_HOUR_ITEM_COUNT,
		ONLINE_REWARD_TIME_CHECK,
		
		// Конец
		INT_VALUE_COUNT
	};

	enum KargatumStringConfigs
	{
		// mod-gm-chat-color
		GM_CHAT_COLOR_LEVEL_3,
		GM_CHAT_COLOR_LEVEL_2,
		GM_CHAT_COLOR_LEVEL_1,

		// Конец
		STRING_VALUE_COUNT
	};

} // conf

class KargatumConfig
{
public:

	static KargatumConfig* instance();
	
	/// Получить с конфига Bool
	bool GetBool(conf::KargatumBoolConfigs index) const
	{
		return index < conf::BOOL_VALUE_COUNT ? m_bool[index] : 0;
	}
	
	/// Получить с конфига Float
	float GetFloat(conf::KargatumFloatConfigs index) const
	{
		return index < conf::FLOAT_VALUE_COUNT ? m_float[index] : 0;
	}

	/// Получить с конфига Int
	int32 GetInt(conf::KargatumIntConfigs index) const
	{
		return index < conf::INT_VALUE_COUNT ? m_int[index] : 0;
	}

	/// Получить с конфига String
	std::string GetString(conf::KargatumStringConfigs index) const
	{
		return index < conf::STRING_VALUE_COUNT ? m_string[index] : 0;
	}

	void LoadConfig();

    IntervalTimer& GetUpdateTimerOnlineReward() { return _UpdateTimerOnlineReward; }

private:
	// Опции конфига
	bool m_bool[conf::BOOL_VALUE_COUNT];
	float m_float[conf::FLOAT_VALUE_COUNT];
	int32 m_int[conf::INT_VALUE_COUNT];
	std::string m_string[conf::STRING_VALUE_COUNT];

    IntervalTimer _UpdateTimerOnlineReward;

    void CheckConfigOption();
    void SetTimers();
};

#define sKargatumConfig KargatumConfig::instance()

#define CONF_BOOL sKargatumConfig->GetBool
#define CONF_INT sKargatumConfig->GetInt
#define CONF_STR sKargatumConfig->GetString
#define CONF_FLOAT sKargatumConfig->GetFloat

#endif // _KARGATUM_CONFIG_H
