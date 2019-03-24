# mod-online-reward

### English readme [->](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-online-reward/README_eng.md)

- Описание
- Конфигурация
- Как использовать
- Настройка в базе данных

### Описание:
Выдача наград за онлайн

### Конфигурация:
```ini
###################################################################################################
#	mod-online-reward
#
#    Online.Reward.Enable
#        Описание: Включить награду за онлайн.
#        По умолчанию: 1
#
#    Online.Reward.Type
#        Описание: Тип выдачи награды. 1 - За сыгранное время, 2 - каждый час
#        По умолчанию: 1
#
#    Online.Reward.Type.Per.Hour.ItemID
#        Описание: Выдаваемый предмет при выбранном типе № 2.
#        По умолчанию: 40265
#
#    Online.Reward.Type.Per.Hour.Item.Count
#        Описание: Количество выдаваемого предмета при выбранном типе № 2.
#        По умолчанию: 1
#
#    Online.Reward.Time.Check
#        Описание: Время проверки в секундах, не ставить меньше 10.
#        По умолчанию: 10
#

Online.Reward.Enable = 1
Online.Reward.Type = 1
Online.Reward.Type.Per.Hour.ItemID = 40265
Online.Reward.Type.Per.Hour.Item.Count = 1
Online.Reward.Time.Check = 10
###################################################################################################
```

### Как использовать:
Настроить конфигурацию под себя и не забыть про БД.

### Настройка в базе данных:
```sql
`world`.`online_reward`
```

- `RewardPlayedTime` - Время (в секундах) которые должен отыграть игрок
- `ItemID` - Номер предмета
- `Count` - Количество предмета

`world`.`online_reward_history` - Используется только для логирования, данную таблицу трогать не нужно, во избежания ошибок
