#
# Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
# Licence MIT https://opensource.org/MIT
#

option(KARGATUM_RUS_LANG     "Включить русский язык в kargatum-system"   1)

if(EXISTS "${KARGATUM_SYSTEM_DIR}/src/mod-cfbg/KargatumCFBG.cpp")
  option(KARGATUM_CFBG     "Enable/disable CFBG"   1)
endif()
