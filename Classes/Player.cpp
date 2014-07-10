//
//  Player.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#include "Player.h"
#include "stdutil.h"
#include "DayRecord.h"
#include "Game.h"

namespace Lemonade {

    
    Player::Player() {
        _money = Item::create("Money");
        _money->inc(200);
        
        _diamond = Item::create("Diamond");
        _diamond->inc(20);
        
        _day = 1;
        _time = 3600*20;
        _activeWorld = 0;
        
        _universe = Lemonade::getUniverse();
		
        _inventory = Inventory::create();
        _inventory->put("Lemon", 40);
        _inventory->put("Cup", 200);
        _inventory->put("Sugar", 100);
    }
    Player::~Player() {
        delete _money;
        delete _diamond;
    }
    
//    const int MAX_INV_SIZE = 20;
    
    bool Player::init() {

		_production_max = (int)getAttrib(toLowerCase(_PRODUCTION_->getName()) + "_production");
        return true;
    }
    
    bool Player::initWithDifficulty(std::string difficulty_level) {
        if (!init()) {
            return false;
        }
        auto plist = FileUtils::getInstance()->getValueMapFromFile("player.plist");
        if (plist.find(difficulty_level)!=plist.end()) {
            ValueMap map = plist[difficulty_level].asValueMap();
            return initWithValueMap(&map);
        }
        return false;
    }

    bool Player::initWithValueMap(ValueMap *map) {
        if (!_inventory) {
            _inventory = Inventory::create();
        }
        
        ValueMap items = map->at("items").asValueMap();
        for (auto iter: items) {
            _inventory->put(iter.first, iter.second.asInt());
        }
        
        if (map->find("money") != map->end() ) {
            _money->setCount(map->at("money").asInt());
        }
        return true;
    }
    
    double Player::getAttrib(std::string name) {
        double attr;
        if ( _attributes.find(name) != _attributes.end() ) {
            attr= _attributes[name];
        } else {
            attr = _inventory->getAttrib(name);
        }
        // Check modifiers;
        for ( auto item: _inventory->getItems() ) {
            ValueMap modifiers = item.second->getModifiers();
            if (modifiers.find(name) != modifiers.end()) {
                attr += modifiers[name].asDouble();
            }
        }
        return attr;
    }
    
    // Production, per hour, return how many production
    int Player::production(std::string item_name, int max_prod) {
        int prod_limit = std::min(_production_max, max_prod);
        int prod = 0;
        _production_result.clear();
        for (int i=1; i<=prod_limit; i++) {
            if (!make(item_name)) {
                break;
            }
            prod = i;
        }
        return prod;
    }
    
    // Get Universe reputation (all worlds)
    int Player::getReputation() {
		
        if (_activeWorld) {
            return (int)_activeWorld->getReputation();
        } else {
            return 0;
        }
    }
    
    // make one item
    bool Player::make(std::string item_name) {
        auto make_item = Item::create(item_name);
//        Inventory* took_items = Inventory::create();
        if ( make_item ) {
            Recipe* recipe = Recipes::getRecipe(item_name);
            bool item_found = false;
            bool make_succ = true;
            for (auto recipe_item: recipe->getIngredients()) {
                // find recipe_item in inventory
                item_found = _inventory->take(recipe_item.item, recipe_item.amount);
                
                if (item_found) {
                    // Item found
                    _production_result[recipe_item.item]+=recipe_item.amount;
//                    CCLOG("%2.1f %s used", recipe_item.amount, recipe_item.item.c_str());
//                    took_items->put(recipe_item.first, recipe_item.second.asDouble());
                } else {
                    make_succ = false;
//                     CCLOG("%2.1f %s recipe item not found", recipe_item.amount, recipe_item.item.c_str());
                    _production_result[recipe_item.item]-=recipe_item.amount;
                }
            }
            // Check if all recipes are used
            if (  make_succ ) {
                _inventory->put(item_name, 1);
//                delete took_items;
                return true;
            } else {
                // put back items, if make failed
                for (auto iter: _production_result) {
                    if (iter.second > 0) {
                        _inventory->put(iter.first, iter.second);
                    }
                }
            }
        }
//        delete recipe_items;
        return false;
    }
    
    bool Player::canSale(std::string item_name, int sales) {
        auto item = _inventory->get(item_name);
        if ((item != NULL) && (item->getCount() >= sales)) {
            return true;
        }
        return false;
    }
    
    bool Player::sale(std::string item_name, int sales) {
        auto item = _inventory->get(item_name);
        if ((item != NULL) && (item->getCount() >= sales)) {
            _inventory->take(item_name, sales);
            double unit_price = item->getPrice();
            _money->inc(unit_price * sales);
            
            DayRecord* day_record = DayRecords::getDayRecord(getDay());
            day_record->setEarned(day_record->getEarned() + unit_price * sales);
            day_record->sold(item_name, sales);
            
            return true;
        }
        return false;
    }
    
    bool Player::canBuy(std::string item_name, int sales) {
        auto item = Item::create(item_name);
        if (item && item->getPrice()) {
            double unit_price = item->getPrice();
            double total_price = unit_price*sales;
            if (_money->getCount() >= total_price) {
                return true;
            }
        }
        return false;
    }
    
    bool Player::buy(std::string item_name, int sales) {
        auto item = Item::create(item_name);
        if (item && item->getPrice()) {
            double unit_price = item->getPrice();
            double total_price = unit_price*sales;
            if (_money->getCount() >= total_price) {
                _money->dec(total_price);
                _inventory->put(item_name, sales);
                
                DayRecord* day_record = DayRecords::getDayRecord(getDay());
                day_record->setSpent(day_record->getSpent() + total_price);
                day_record->bought(item_name, sales);
                
                return true;
            }
        }
        return false;
    }

    void Player::loadFromValueMap(ValueMap &map) {
        
        if (map.find("diamond") != map.end())
            _money->setCount(map["diamond"].asDouble());
        
        if (map.find("money") != map.end())
            _money->setCount(map["money"].asDouble());
        
        if (map.find("inventory") != map.end())
            _inventory->loadFromValueMap(map["inventory"].asValueMap());
        
        if (map.find("recipes") != map.end())
            Recipes::loadFromValueMap(map["recipes"].asValueMap());
        
        // Loads Worlds
        if (map.find("universe") != map.end())
            Lemonade::loadUniverseFromValueMap(_universe, map["universe"].asValueMap());

    }
    
    void Player::saveToValueMap(ValueMap &map) {
        map["diamond"] = (int)_diamond->getCount();
        map["money"] = _money->getCount();
        ValueMap invmap;
        _inventory->saveToValueMap(invmap);
        map["inventory"] = invmap;
        
        ValueMap recipes_map;
        Recipes::saveToValueMap(recipes_map);
        map["recipes"] = recipes_map;
        
        // Save Worlds
        ValueMap worlds_map;
        Lemonade::saveUniverseToValueMap(_universe, worlds_map);
        map["universe"] = recipes_map;
    }
    
    void Player::enterWorld(Lemonade::World *world) {
        DayRecord* day_record = DayRecords::getDayRecord(getDay());
        this->setActiveWorld(world);
        
        day_record->setSpent(day_record->getSpent() + _activeWorld->getPrice());
        
    }
    
    bool Player::buyGold(int diamonds) {
        if (diamonds < _GAME_.getMinDiamondGold()) {
            // Less than minimum diamond to convert
            return false;
        }
        if (incDiamond(-diamonds)) {
            incMoney(diamonds * _GAME_.getGoldPerDiamond());
            return true;
        }
        return false;
    }
    
    bool Player::incMoney(int coins) {
        if ((getMoney()->getCount() + coins) < 0) {
            return false;
        }
        getMoney()->inc(coins);
        return true;
    }
    
    bool Player::incDiamond(int diamonds) {
        if ((getDiamond()->getCount() + diamonds) < 0) {
            return false;
        }
        getDiamond()->inc(diamonds);
        return true;
    }
    
    void Player::incDay(int day) {
        setDay(getDay()+day);
    }
}