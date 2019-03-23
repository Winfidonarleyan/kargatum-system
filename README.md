# Kargatum System [![Build Status](https://travis-ci.com/Winfidonarleyan/kargatum-system.svg?branch=master)](https://travis-ci.com/Winfidonarleyan/kargatum-system)

# Главное меню / Main menu

#### Паблик скрипты / Public scripts
- **mod-anti-advertisment**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-anti-advertisment)
- * English description

- **mod-auto-revive**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-auto-revive)
- * English description

- **mod-bg-reward**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-bg-reward)
- * English description

- **mod-buff-command**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-buff-command)
- * English description

- **mod-faction-icons-channel**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-faction-icons-channel)
- * English description

- **mod-gm-chat-color**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-gm-chat-color)
- * English description

- **mod-level-reward**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-level-reward)
- * English description

- **mod-notify-muted**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-notify-muted)
- * English description

- **mod-online-reward**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-online-reward)
- * English description

- **mod-player-login**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-player-login)
- * English description

- **mod-spell-duration**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-spell-duration)
- * English description

#### Приват скрипты / Private scripts
- **mod-crossfaction-bg**
- * Русское описание
- * English description

### Чтобы включить поддержку русского языка
Нужно раскомментировать данную строку в файле [KargatumConfig.h#L13](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/Kargatum-lib/KargatumConfig.h#L13). В итоге должно получить вот так. 
```cpp
#define KARGATUM_RUS_LANG
```

--------- 
### mod-spell-duration
Модифицирование времени заклинаний (в бд, без исправления в дбц)

## Приватные

### mod-crossfaction-bg
Один из популярнейших скриптов, который меняет фракцию игрока на поле боя, которая в меньшенстве.

------

## Public scripts
### mod-anti-advertisment
Not allows to write in the chat the forbidden words.

### mod-auto-revive 
Auto resurrection at death only for GM

### mod-bg-reward
If you win or lose on the battleground, you get an additional reward

### mod-buff-command
Add custom command `.buff` for self buff

### mod-faction-icons-channel
Display fraction incons in chat channels (for server common chat)

### mod-gm-chat-color
Change color chat with gm badge in chats

### mod-level-reward
Reward players for level up

### mod-notify-muted
Notifies player (who wrote a private message) that his interlocutor can not talk (if his chat is not available)

### mod-online-reward
Reward players for online

### mod-player-login
Display info at login in game world

### mod-spell-duration
Modifing duration spells in database (not dbc)

## Private

### mod-crossfaction-bg
One of the most popular scripts that change the player's faction on the battlefield, which is in the minority.
