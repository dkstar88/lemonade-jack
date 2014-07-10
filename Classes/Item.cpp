//
//  Item.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-9.
//
//

#include "Item.h"

namespace Lemonade {

    bool Item::init() {

        return true;
    }
    
    std::string Item::getDescription() const {
        return StringUtils::format("Item[%s: %d]", _name.c_str(), (int)_count);
    }
    
    void Item::setTaste(Lemonade::Taste *var) {
        _taste = var;
    }
    
    Taste* Item::getTaste() {
        auto recipe = Recipes::getRecipe(_name);
        if (recipe) {
            return &recipe->getTaste();
        } else {
            return _taste;
        }
    }
    
    double Item::getPrice() {
        auto recipe = Recipes::getRecipe(_name);
        if (recipe) {
            return recipe->getPrice();
        } else {
            return _price;
        }
    }
    
    void Item::setPrice(double var) {
        _price = var;
    }
    
    bool Item::initWithName(std::string name) {
        if (init()) {
            setName(name);
            return true;
        } else {
            return false;
        }
    }
    
    bool Item::setItemName(std::string name) {
        ValueMap p_vec = FileUtils::getInstance()->getValueMapFromFile("items.plist");
        for( auto iter : p_vec)
        {
            if (name == iter.first) {
                _name = iter.first;
                ValueMap data = iter.second.asValueMap();
                _price = data["price"].asDouble();
                _icon = data["icon"].asString();
                if (data.find("price_var") != data.end()) {
                    _price_var = data["price_var"].asDouble();
                }
                if (data.find("modifier") != data.end() ) {
                    _modifiers = data["modifier"].asValueMap();
                }
                if (data.find("recipe") != data.end()) {
                    _recipe = Recipe::createWithIngredients(data["recipe"].asValueMap());
                }
                if (data.find("attrib") != data.end()) {
                    _attributes = data["attrib"].asValueMap();
                }
                if (data.find("sellable") != data.end()) {
                    _sellable = data["sellable"].asBool();
                }
                if (data.find("taste") != data.end()) {
					if (_taste) delete _taste;
                    ValueMap tastemap = data["taste"].asValueMap();
                    _taste = Lemonade::Taste::createFromValueMap(&tastemap);
//                    CCLOG("%s Taste: %s", _name.c_str(), _taste->getDescription().c_str());
                }
            }
        }
        return true;
    }
    
    double Item::inc(double val) {
        _count += val;
        return _count;
    }
    
    double Item::dec(double val) {
        _count -= val;
        return _count;
    }
    
    double Item::getAttrib(std::string item_attrib_name) {
        double attr_val = 0;
        ValueMap _items = FileUtils::getInstance()->getValueMapFromFile("items.plist");
        
        for ( auto iter: _items ) {
            std::string item_name = toLowerCase(iter.first);
            ValueMap data = iter.second.asValueMap();
            if (data.find("attrib") != data.end()) {
                ValueMap _attributes = data["attrib"].asValueMap();
                for (auto attr: _attributes) {
                    std::string item_attr = item_name + "_" + attr.first;
                    if (item_attr == item_attrib_name) {
                        attr_val = attr.second.asDouble();
                        return attr_val;
                    }
                }
            }
        }
        return attr_val;
    }
    
    Item* Item::create(std::string name, std::string icon, double price, double price_var, int shelf_life, double demand)
    {
        Item *pRet = new Item();
        if (pRet && pRet->init())
        {
            pRet->setName(name);
            pRet->setIcon(icon);
            pRet->setPrice(price);
            pRet->setPriceVar(price_var);
            pRet->setShelfLife(shelf_life);
            pRet->setDemand(demand);
            //                    pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return pRet;
        }
    }
    
    Item* Item::create(std::string name)
    {
        Item *pRet = new Item();
        if (pRet && pRet->init() && pRet->setItemName(name))
        {
            //                    pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return pRet;
        }
    }

    void Item::saveToValueMap(ValueMap &map) {
//        map[""]
    }
    
    void Item::loadFromValueMap(ValueMap &map) {
        
    }

	Item::~Item()
	{
		if (_taste) delete _taste;
		if (_recipe) delete _recipe;
	}

	Item::Item()
	{
		_count = 0;
		_price = 0;
		_price_var = 0;
		_demand = 0.3;
		_recipe = NULL;
		_taste = NULL;
	}

}