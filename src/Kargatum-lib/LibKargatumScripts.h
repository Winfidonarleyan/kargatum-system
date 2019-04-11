/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef LIBKARGATUM_SCRIPT_H
#define LIBKARGATUM_SCRIPT_H

#ifndef KARGATUMCORE
#include "Common.h"
#include "Player.h"

class LibKargatumScript
{
public:
    static LibKargatumScript* instance();

    std::string GetMoneyString(uint32 Gold);
    std::string GetFormatString(const char* format, ...) ATTR_PRINTF(2, 3);

    void SendMailPlayer(Player* player, std::string Subject, std::string Text, uint32 ItemEntry, uint32 ItemCount);
};

#define sKargatumScript LibKargatumScript::instance()
#endif // KARGATUMCORE

#endif // LIBKARGATUM_SCRIPT_H
