# mod-anti-advertisment

### Русское описание [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-anti-advertisment)

- Description
- Configuration
- How to use
- Use in database

### Description:
Not allows to write in the chat the forbidden words.

### Configuration:
```ini
###################################################################################################
#	mod-anti-advertisment
#
#    AntiAD.Enable
#        Description: Enable system forbidden words.
#        Default: 1
#
#    AntiAD.Message.GM.World.Enable
#        Description: Enable notify all GMs.
#        Default: 1
#
#    AntiAD.FullMessage.GM.World.Enable
#        Description: Enable notify full message all GMs.
#        Default: 1
#
#    AntiAD.Message.Self.Enable
#        Description: Show forbidden word message self.
#        Default: 1
#
#    AntiAD.Enable.Mute
#        Description: Enable mute at writing forbidden word.
#        Default: 1
#
#    AntiAD.Mute.GM 
#        Description: Enable mute for GMs.
#        Default: 0
#
#    AntiAD.Mutetime 
#        Description: Mute time in minutes.
#        Default: 5
#

AntiAD.Enable = 1
AntiAD.Message.GM.World.Enable = 1
AntiAD.FullMessage.GM.World.Enable = 1
AntiAD.Message.Self.Enable = 1
AntiAD.Enable.Mute = 1
AntiAD.Mute.GM = 0
AntiAD.Mutetime = 1
###################################################################################################
```

### How to use:
Change config and try to write in chat forbidden words, example `wow`

### Use in database:
```sql
`world`.`anti_ad_message`
```

- `message` - Forbidden words


