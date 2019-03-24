/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef KARGATUM_LOAD_H
#define KARGATUM_LOAD_H

#include "Common.h"
#include <vector>
#include <map>

// struct LevelUPItem
// {
// 	uint32 MinLevel;
// 	uint32 MaxLevel;
// };

struct RewardPlayedTime
{
    uint32 ItemID;
    uint32 Count;
};

struct LevelReward
{
    uint32 Money;    
    uint32 ItemID;
    uint32 ItemCount;
};

enum TypeReward
{
    DEFAULT_REWARD = 1,
    REWARD_PER_HOUR
};

class KargatumLoad
{
public:
	
	static KargatumLoad* instance();
    
    void LoadKargatumSystem();    
	void LoadMessageAntiAD();	
	void LoadBuffData();
	// void LoadLevelUPItem();
    void LoadPlayedTimeReward();
    void LoadLevelReward();

	typedef std::vector<std::string> ChatMuteContainer;
    typedef std::vector<uint32> BuffDataContainer;
	// typedef std::map<uint32, LevelUPItem> LevelUPItemContainer;
    typedef std::map<uint32, RewardPlayedTime> RewardPlayedTimeContainer;
    typedef std::map<uint32, LevelReward> LevelRewardContainer;

	ChatMuteContainer &GetAntiADMesages() { return _AntiAdMessageStore; }	
	BuffDataContainer &GetBuffData() { return _BuffDataStore; }
	//LevelUPItemContainer &GetLevelUPItem() { return _LevelUPItemDataStore; }
    RewardPlayedTimeContainer &GetRewardPlayedTime() { return _RewardPlayedTimeStore; }    
    LevelRewardContainer &GetRewardLevel() { return _levelRewardStore; }

private:

	ChatMuteContainer _AntiAdMessageStore;
	BuffDataContainer _BuffDataStore;
	//LevelUPItemContainer _LevelUPItemDataStore;
    RewardPlayedTimeContainer _RewardPlayedTimeStore;
    LevelRewardContainer _levelRewardStore;
};

#define sKargatumLoad KargatumLoad::instance()

#endif // KARGATUM_LOAD_H
