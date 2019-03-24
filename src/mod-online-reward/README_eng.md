# mod-online-reward

### Русское описание [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-online-reward)

- Description
- Configuration
- How to use
- Use database

### Description:
Reward players for online

### Configuration:
```ini
###################################################################################################
#	mod-online-reward
#
#    Online.Reward.Enable
#        Description: Enable online reward.
#        Default: 1
#
#    Online.Reward.Type
#        Description: Reward online type. 1 - Default (playing second), 2 - per hour.
#        Default: 1
#
#    Online.Reward.Type.Per.Hour.ItemID
#        Description: Reward item number at type # 2.
#        Default: 40265
#
#    Online.Reward.Type.Per.Hour.Item.Count
#        Description: Reward item count at type # 2.
#        Default: 1
#
#    Online.Reward.Time.Check
#        Description: Time check for system.
#        Default: 10
#

Online.Reward.Enable = 1
Online.Reward.Type = 1
Online.Reward.Type.Per.Hour.ItemID = 40265
Online.Reward.Type.Per.Hour.Item.Count = 1
Online.Reward.Time.Check = 10
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
