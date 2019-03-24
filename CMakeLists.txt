#
# Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
# Licence MIT https://opensource.org/MIT
#

if (KARGATUMCORE)
    message("-- Обнаружено ядро KargatumCore. Загрузка модуля kargatum-system отменена")
endif()

if (NOT KARGATUMCORE)

message("-> Loading Kargatum System")

# Set dir
set(KARGATUM_LIB_DIR    "${CMAKE_CURRENT_LIST_DIR}/src/Kargatum-lib")
set(KARGATUM_SC_DIR     "${CMAKE_CURRENT_LIST_DIR}/src")
set(KARGATUM_CONF_DIR   "${CMAKE_CURRENT_LIST_DIR}/conf")

# Add kargatum lib
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumConfig.cpp")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumConfig.h")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumLoadSystem.cpp")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumLoadSystem.h")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumScripts.cpp")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumScripts.h")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/KargatumLanguage.h")

message("-> Loaded library Kargatum-lib")

# Add cpp files
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-anti-advertisment/KargatumAntiAdvertisment.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-auto-revive/KargatumAutoRevive.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-bg-reward/KargatumBGReward.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-buff-command/KargatumBuffCommand.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-faction-icons-channel/KargatumIconFaction.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-gm-chat-color/KargatumGmChatColor.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-level-reward/KargatumLevelReward.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-notify-muted/KargatumPlayerNotSpeak.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-online-reward/KargatumOnlineReward.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-player-info-login/KargatumPlayerInfoLogin.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-spell-duration/KargatumSpellDuration.cpp")

# Add scripts to script loader
AC_ADD_SCRIPT_LOADER("Kargatum" "${CMAKE_CURRENT_LIST_DIR}/src/KargatumSCLoad.h")

# Add config file
AC_ADD_CONFIG_FILE("${KARGATUM_CONF_DIR}/KargatumSystem.conf.dist")

# English config
# AC_ADD_CONFIG_FILE("${KARGATUM_CONF_DIR}/KargatumSystem_eng.conf.dist")

message("-> Loaded custom scripts")

endif()

