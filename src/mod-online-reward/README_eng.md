# mod-online-reward

### Русское описание [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-online-reward)

- Description
- Configuration
- How to use
- Use database

### Description:
Reward players for online
- Type 1 One-time awards to players when a certain amount of time has been played (total number in skunks). Awards are indicated in the database. `world`.`online_reward`
- Type 2 Periodic (cyclic) reward for the player's presence in the game (the number determines the periodicity with which the awards will be given - in seconds)

### Configuration:
```ini
###################################################################################################
#	mod-online-reward
#
#    Online.Reward.Enable
#        Description: Include the entire online rewards module
#        Default: 1
#
#    Online.Reward.Per.Online.Enable
#        Description: Enable Type 1 (awards for general online on the server).
#        Default: 1
#
#    Online.Reward.Per.Time.Enable
#        Description: Type 2 (periodic awards for periods of time).
#        Default: 1
#
#    Online.Reward.Per.Time.Time
#        Description: The period of time after which the award will be given (type 2). In seconds
#        Default: 3600 (1 hour)
#
#    Online.Reward.Per.Time.ItemID
#        Description: The item to be given out during the periodic issue. (Type 2)
#        Default: 47241 (The emblem of triumph)
#
#    Online.Reward.Per.Time.Item.Count
#        Description: Reward item count for reward type per time. (Type 2)
#        Default: 1
#
#    Online.Reward.Check.Time
#        Description: The time after which the module performs the verification to determine the awarding of awards in both types (number in seconds)
#        Default: 60 (1 minute)
#

Online.Reward.Enable = 1
Online.Reward.Per.Online.Enable = 1
Online.Reward.Per.Time.Enable = 1
Online.Reward.Per.Time.Time = 3600
Online.Reward.Per.Time.ItemID = 47241
Online.Reward.Per.Time.Item.Count = 1
Online.Reward.Check.Time = 60
###################################################################################################
```

### How to use:
Change config and change data in databse

### Use database:
```sql
`world`.`online_reward`
```
- `RewardPlayedTime` - Time (in seconds) for reward
- `ItemID` - Item nubmer
- `Count` - Item count

`world`.`online_reward_history` - This table for only loggin, don't change table!
