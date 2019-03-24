# mod-level-reward

### Русское описание [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-level-reward)

- Description
- Configuration
- How to use
- Use database

### Description:
Reward players for level up

### Configuration:
```ini
###################################################################################################
#	mod-level-reward
#
#    Level.Reward.Enable
#        Description: Enable level up reward system.
#        Default: 1
#

Level.Reward.Enable = 1
###################################################################################################
```

### How to use:
Change conf and change data in database. Try level up.

### Use database:
```sql
`world`.`level_reward`
```

- `Level` - Level
- `Money` - Money
- `ItemID` - Item number
- `ItemCount` - Item count
