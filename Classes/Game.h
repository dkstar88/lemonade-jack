//
//  Game.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#ifndef __teaegg__Game__
#define __teaegg__Game__

#include "Items.h"
#include "World.h"
#include "Recipe.h"
#include "People.h"
#include "cocos2d.h"

USING_NS_CC;

namespace Lemonade {
    
    class Game {
    public:
        
        static Game& getInstance();
        virtual bool init();
        CC_SYNTHESIZE(ValueMap, _defaults, Defaults);
        CC_SYNTHESIZE(int, _speed, Speed);
        CC_SYNTHESIZE(int, _min_diamond_gold, MinDiamondGold);
        CC_SYNTHESIZE(int, _gold_per_diamond, GoldPerDiamond);
        Item* getProductionItem();
    
    protected:
        Item* _production_item = NULL;
        
    };
    
    
}


#define _GAME_ Lemonade::Game::getInstance()
#define _PRODUCTION_ Lemonade::Game::getInstance().getProductionItem()
#define _GAME_SPEED_ (float)(Lemonade::Game::getInstance().getSpeed())
#endif /* defined(__teaegg__Game__) */
