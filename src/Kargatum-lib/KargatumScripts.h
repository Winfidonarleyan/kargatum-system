/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef KARGATUM_SCRIPT_H
#define KARGATUM_SCRIPT_H

#include "Common.h"
#include "Player.h"

class KargatumScript
{
public:
    static KargatumScript* instance();

    std::string GetMoneyString(uint32 Gold);
    std::string GetFormatString(const char* format, ...) ATTR_PRINTF(2, 3);

    void SendMailPlayer(Player* player, std::string Subject, std::string Text, uint32 ItemEntry, uint32 ItemCount);
};

#define sKargatumScript KargatumScript::instance()

#endif
