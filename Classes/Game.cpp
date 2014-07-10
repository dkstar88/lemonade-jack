//
//  Game.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#include "Game.h"

namespace Lemonade {
    
    static Game* _game = NULL;
    
    Game& Game::getInstance() {
        if (!_game) {
            _game = new Game();
            _game->init();
        }
        return *_game;
    }
    
    Item* Game::getProductionItem() {
        if (!_production_item) {
            _production_item = Item::create(_defaults["production"].asString());
        }
        
        return _production_item;
    }
    
    bool Game::init() {
        _speed = 2;
        _defaults = FileUtils::getInstance()->getValueMapFromFile("game.plist");
        _min_diamond_gold = _defaults["min_diamond_gold"].asInt();
        _gold_per_diamond = _defaults["gold_per_diamond"].asInt();
        return true;
    }
}

