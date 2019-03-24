# mod-spell-duration

## This module not complete!

### Русское описание [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-spell-duration)

- Description
- Configuration
- How to use
- Use database

### Description:
Modifing duration spells in database

### Configuration:
```ini
###################################################################################################
#	mod-spell-duration
#
#    Spell.Duration.Enable
#        Description: Включить систему смены времени заклинаний.
#        Default: 1
#

Spell.Duration.Enable = 1
###################################################################################################
```

### How to use:
Настроить конфигурацию под себя, а так же настроить БД.

### Use database:
```sql
`world`.`online_reward`
```
- `SpellID` - Spell number
- `MaxDuration` - Time duration. `-1` - permanent
