/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef _KARGATUM_SCRIPTS_LOADER_H_
#define _KARGATUM_SCRIPTS_LOADER_H_

// From Lib
void AddSC_Kargatum_Startup();

// From SC
void AddSC_Kargatum_AntiAdvertisment();
void AddSC_Kargatum_Auto_Revive();
void AddSC_Kargatum_BGReward();
void AddSC_Kargatum_BuffCommand();
void AddSC_Kargatum_IconFaction();
void AddSC_Kargatum_GMChatColor();
void AddSC_Kargatum_LevelReward();
void AddSC_Kargatum_PlayerNotSpeak();
void AddSC_Kargatum_OnlineReward();
void AddSC_Kargatum_PlayerLoginInfo();
void AddSC_Kargatum_SpellDuration();

// Add all
void AddKargatumScripts()
{
    // Lib
    AddSC_Kargatum_Startup();

    // SC
    AddSC_Kargatum_AntiAdvertisment();
    AddSC_Kargatum_Auto_Revive();
    AddSC_Kargatum_BGReward();
    AddSC_Kargatum_BuffCommand();
    AddSC_Kargatum_IconFaction();
    AddSC_Kargatum_GMChatColor();
    AddSC_Kargatum_LevelReward();
    AddSC_Kargatum_PlayerNotSpeak();
    AddSC_Kargatum_OnlineReward();
    AddSC_Kargatum_PlayerLoginInfo();
    AddSC_Kargatum_SpellDuration();
}

#endif /* _KARGATUM_SCRIPTS_LOADER_H_ */


