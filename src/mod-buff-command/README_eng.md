# mod-buff-command

### Русское описание [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-buff-command)

- Description
- Configuration
- How to use
- Use database

### Description:
Add custom command .buff for self buff
With this command, all the rip-offs specified in the table are applied to the character `world`.`player_buff`

### Configuration:
```ini
###################################################################################################
#	mod-buff-command
#
#    Buff.Command.Enable
#        Description: Enable the ability to use the command .buff.
#        Default: 1
#

Buff.Command.Enable = 1
###################################################################################################
```

### How to use:
Change conf and change data in database

### Use databse:
```sql
`world`.`player_buff`
```

- `SpellID` - Spell number
- `Comment` - You comment
