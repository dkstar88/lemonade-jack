//
//  Player.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#ifndef __lemoname__Player__
#define __lemoname__Player__

#include "cocos2d.h"
#include "Items.h"
#include "World.h"

USING_NS_CC;

namespace Lemonade {
    
    typedef std::map<std::string, double> AttribMap;
    
    const std::string DIFFICULTY_LEVEL_EASY = "easy";
    const std::string DIFFICULTY_LEVEL_MEDIUM = "medium";
    const std::string DIFFICULTY_LEVEL_HARD = "hard";
    
    class Player {
    public:
        virtual bool init();
        bool initWithDifficulty(std::string difficulty_level);
        bool initWithValueMap(ValueMap *map);
        bool make(std::string item_name);
        double getAttrib(std::string name);
        int production(std::string item_name, int max_prod);
        bool sale(std::string item_name, int sales);
        bool canSale(std::string item_name, int sales);
        bool buy(std::string item_name, int sales);
        bool canBuy(std::string item_name, int sales);
        
        bool buyGold(int diamonds);
        bool incMoney(int coins);
        bool incDiamond(int diamonds);
        void incDay(int day=1);
        int getReputation();
        
        
        void loadFromValueMap(ValueMap &map);
        void saveToValueMap(ValueMap &map);
        void enterWorld(World* world);
        
        
        CC_SYNTHESIZE(int, _status, Status);
        CC_SYNTHESIZE(time_t, _time, Time);
        CC_SYNTHESIZE(int, _day, Day);
        
        CC_SYNTHESIZE(Universe, _universe, Universe);
        CC_SYNTHESIZE(World*, _activeWorld, ActiveWorld);
        
        CC_SYNTHESIZE(AttribMap, _attributes, Attributes);
        CC_SYNTHESIZE(Inventory*, _inventory, Inventory);
        CC_SYNTHESIZE(Item*, _money, Money);
        CC_SYNTHESIZE(Item*, _diamond, Diamond);
        CC_SYNTHESIZE_READONLY_PASS_BY_REF(ItemsCount, _production_result, ProductionResult);
        
        Player();
        virtual ~Player();
        static Player* create() {
            Player* obj = new Player();
            if (obj->init()) {
                return obj;
            } else {
                return NULL;
            }
        }

	private:
		int _production_max;
//        CREATE_FUNC(Player);
    };
    
    
}

#endif /* defined(__lemoname__Player__) */
