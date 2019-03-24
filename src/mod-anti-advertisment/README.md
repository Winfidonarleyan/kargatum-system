# mod-anti-advertisment

### English readme [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-anti-advertisment/README_eng.md)

- Описание
- Конфигурация
- Как использовать
- Настройка в базе данных

### Описание:
Запрет использования запрещенных слов в чате.

### Конфигурация:
```ini
###################################################################################################
#	mod-anti-advertisment
#
#    AntiAD.Enable
#        Описание: Включить систему запретных слов.
#        По умолчанию: 1
#
#    AntiAD.Message.GM.World.Enable
#        Описание: Включить оповещение всем ГМам.
#        По умолчанию: 1
#
#    AntiAD.FullMessage.GM.World.Enable
#        Описание: Включить полное сообщение всем ГМам.
#        По умолчанию: 1
#
#    AntiAD.Message.Self.Enable
#        Описание: Показыть запретное сообщение нарушившему.
#        По умолчанию: 1
#
#    AntiAD.Enable.Mute
#        Описание: Включить мут при написании запретного слова.
#        По умолчанию: 1
#
#    AntiAD.Mute.GM 
#        Описание: Включить мут для ГМов.
#        По умолчанию: 0
#
#    AntiAD.Mutetime 
#        Описание: Время мута в минутах.
#        По умолчанию: 5
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

### Как использовать:
Настроить конфигурацию под себя и попробовать написать запретное слово, например `wow`

### Настройка в базе данных:
```sql
`world`.`anti_ad_message`
```

- `message` - Запрещённое слово
