/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef LIBKARGATUM_SCRIPT_H
#define LIBKARGATUM_SCRIPT_H

#ifndef KARGATUMCORE
#include "Common.h"
#include "Player.h"

typedef std::pair<uint32, uint32> KargatumMailItemPair;
typedef std::vector<KargatumMailItemPair> KargatumMailVector;

class KargatumScript
{
public:
    static KargatumScript* instance();

    std::string GetMoneyString(uint32 Gold);
    std::string GetFormatString(const char* format, ...) ATTR_PRINTF(2, 3);

    void SendMailPlayer(Player* player, std::string Subject, std::string Text, uint32 ItemEntry, uint32 ItemCount);
    void SendMoreItemsMail(Player* player, std::string Subject, std::string Text, uint32 Money, KargatumMailVector ListItemPairs);
};

#define sKargatumScript KargatumScript::instance()
#endif // KARGATUMCORE

#endif // LIBKARGATUM_SCRIPT_H
