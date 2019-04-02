# Kargatum System [![Build Status](https://travis-ci.com/Winfidonarleyan/kargatum-system.svg?branch=master)](https://travis-ci.com/Winfidonarleyan/kargatum-system)

# Главное меню / Main menu

#### Паблик скрипты / Public scripts
- **mod-anti-advertisment**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/tree/master/src/mod-anti-advertisment)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-anti-advertisment/README_eng.md)

- **mod-auto-revive**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-auto-revive)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-auto-revive/README_eng.md)

- **mod-bg-reward**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-bg-reward)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-bg-reward/README_eng.md)

- **mod-buff-command**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-buff-command)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-buff-command/README_eng.md)

- **mod-faction-icons-channel**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-faction-icons-channel)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-faction-icons-channel/README_eng.md)

- **mod-gm-chat-color**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-gm-chat-color)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-gm-chat-color/README_eng.md)

- **mod-level-reward**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-level-reward)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-level-reward/README_eng.md)

- **mod-notify-muted**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-notify-muted)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-notify-muted/README_eng.md)

- **mod-online-reward**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-online-reward)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-online-reward/README_eng.md)

- **mod-player-info-login**
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-player-info-login)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-player-info-login/README_eng.md)

- **mod-spell-duration** Coming soon... / Скоро...
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-spell-duration)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-spell-duration/README_eng.md)

- **mod-auto-loot** Coming soon... / Скоро...
- * [Русское описание](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-auto-loot)
- * [English description](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/mod-auto-loot/README_eng.md)

#### Приват скрипты / Private scripts
- **mod-crossfaction-bg** Coming soon... / Скоро...
- * Русское описание
- * English description

### For enable eng language in config and game world
- For game world 
Need uncomment line in file [KargatumConfig.h#L13](https://github.com/Winfidonarleyan/kargatum-system/blob/master/src/Kargatum-lib/KargatumConfig.h#L13). Should be like this
```cpp
// #define KARGATUM_RUS_LANG
```
- For config
Comment line in file [CMakeLists.txt#L47](https://github.com/Winfidonarleyan/kargatum-system/blob/master/CMakeLists.txt#L47).
```Cmake
# AC_ADD_CONFIG_FILE("${KARGATUM_CONF_DIR}/KargatumSystem.conf.dist")
```
And uncomment line in the same file [CMakeLists.txt#L50](https://github.com/Winfidonarleyan/kargatum-system/blob/master/CMakeLists.txt#L50).
```Cmake
AC_ADD_CONFIG_FILE("${KARGATUM_CONF_DIR}/KargatumSystem_eng.conf.dist")
```

### Credits
- Autor system - [Winfidonarleyan](https://github.com/Winfidonarleyan)
- [Discord channel for system](https://discord.gg/xCwPqdq)
- [Discord channel for AzerothCore](https://discord.gg/PaqQRkd)
