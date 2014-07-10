//
//  GameVars.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#ifndef lemoname_GameVars_h
#define lemoname_GameVars_h

#include "Player.h"
#include "World.h"

class GlobalVars {
public:
    static Lemonade::Player* getPlayer();
    
    static void LoadGame();
    static void SaveGame();
    static void NewGame();
    
protected:
    static Lemonade::Player* player;
    
};

#define _PLAYER_ GlobalVars::getPlayer()

#endif
