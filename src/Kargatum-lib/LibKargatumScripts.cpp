/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef KARGATUMCORE
#include "LibKargatumScripts.h"
#include "DatabaseEnv.h"
#include "Player.h"
#include "Log.h"

KargatumScript* KargatumScript::instance()
{
    static KargatumScript instance;
    return &instance;
}

std::string KargatumScript::GetMoneyString(uint32 Gold)
{
    uint32 gold = Gold / GOLD;
    uint32 silv = (Gold % GOLD) / SILVER;
    uint32 copp = (Gold % GOLD) % SILVER;

    return this->GetFormatString("%u|TInterface\\MoneyFrame\\UI-GoldIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-SilverIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-CopperIcon:0:0:2:0|t", gold, silv, copp);
}

std::string KargatumScript::GetFormatString(const char* format, ...)
{
    va_list ap;
    char str[2048];
    va_start(ap, format);
    vsnprintf(str, 2048, format, ap);
    va_end(ap);
    return std::string(str);
}

void KargatumScript::SendMailPlayer(Player* player, std::string Subject, std::string Text, uint32 ItemEntry, uint32 ItemCount)
{
    // from console show not existed sender
    MailSender sender(MAIL_NORMAL, player->GetGUIDLow(), MAIL_STATIONERY_DEFAULT);

    // fill mail
    MailDraft draft(Subject, Text);

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    if (Item * item = Item::CreateItem(ItemEntry, ItemCount, player))
    {
        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
        draft.AddItem(item);
    }

    draft.SendMailTo(trans, player, sender);
    CharacterDatabase.CommitTransaction(trans);
}

void KargatumScript::SendMoreItemsMail(Player* player, std::string Subject, std::string Text, uint32 Money, KargatumMailVector ListItemPairs)
{
    if (ListItemPairs.size() > MAX_MAIL_ITEMS)
    {
        sLog->outError("> KargatumScript::SendMoreItemsMail: ListItemPairs.size() = %u", (uint32)ListItemPairs.size());
        return;
    }

    KargatumMailVector _listItemPairs;

    // check
    for (auto itr : ListItemPairs)
    {
        uint32 ItemID = itr.first;
        uint32 ItemCount = itr.second;

        ItemTemplate const* item = sObjectMgr->GetItemTemplate(ItemID);
        if (!item)
            continue;

        if (ItemCount < 1 || (item->MaxCount > 0 && ItemCount > uint32(item->MaxCount)))
            break;

        while (ItemCount > item->GetMaxStackSize())
        {
            _listItemPairs.push_back(KargatumMailItemPair(ItemID, item->GetMaxStackSize()));
            ItemCount -= item->GetMaxStackSize();
        }

        _listItemPairs.push_back(KargatumMailItemPair(ItemID, ItemCount));

        if (_listItemPairs.size() > MAX_MAIL_ITEMS)
        {
            sLog->outError("> KargatumScript::SendMoreItemsMail: _listItemPairs.size() = %u", (uint32)_listItemPairs.size());
            break;
        }
    }

    // from console show not existed sender
    MailSender sender(MAIL_NORMAL, player->GetGUIDLow(), MAIL_STATIONERY_DEFAULT);

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    // fill mail
    MailDraft draft(Subject, Text);

    for (auto itr : _listItemPairs)
    {
        if (Item * item = Item::CreateItem(itr.first, itr.second, player))
        {
            item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
            draft.AddItem(item);
        }
    }

    if (Money)
        draft.AddMoney(Money);

    draft.SendMailTo(trans, player, sender);
    CharacterDatabase.CommitTransaction(trans);
}
#endif
