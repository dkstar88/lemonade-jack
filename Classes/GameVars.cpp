//
//  GameVars.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#include "GameVars.h"
#include "cocos2d.h"

USING_NS_CC;

using namespace Lemonade;


Player* GlobalVars::player;

Player* GlobalVars::getPlayer() {
    if (player == NULL) {
        player = Player::create();
        CCLOG("*********** Player created ***********");
    }
    return player;
}

void GlobalVars::NewGame() {

    ValueMap data = FileUtils::getInstance()->getValueMapFromFile("default.plist");
    _PLAYER_->loadFromValueMap(data);

}

void GlobalVars::LoadGame() {
    std::string filepath = StringUtils::format("%s/%s", FileUtils::getInstance()->getWritablePath().c_str(), "current/player.plist");
    
    if (FileUtils::getInstance()->isFileExist(filepath)) {
        ValueMap data = FileUtils::getInstance()->getValueMapFromFile(filepath);
        _PLAYER_->loadFromValueMap(data);
    } else {
        GlobalVars::NewGame();
    }

}

void GlobalVars::SaveGame() {
    std::string filepath = StringUtils::format("%s/%s", FileUtils::getInstance()->getWritablePath().c_str(), "current/player.plist");
    
    ValueMap data;
    _PLAYER_->saveToValueMap(data);
    
    FileUtils::getInstance()->writeToFile(data, filepath);
}