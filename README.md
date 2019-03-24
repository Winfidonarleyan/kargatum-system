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