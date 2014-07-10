//
//  Inventory.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#include "Inventory.h"
#include "stdutil.h"

namespace Lemonade {

        std::string Inventory::getDescription() const {
            std::string s = "";
            for (auto item: _items) {
                s += item.second->getDescription() + ", ";
            }
            return "Inventory[" + s + "]";
        }
        bool Inventory::init() {

            return true;
        }
        Item* Inventory::get(std::string name) {
            if (_items.find(name) != _items.end()) {
                return _items[name];
            } else {
                return NULL;
            }
        }
        
        Item* Inventory::get(std::string name, bool forceCreate) {
            if (forceCreate) {
                return put(name);
            } else {
                return get(name);
            }
        }
    
        Item* Inventory::put(std::string name) {
            Item* item = get(name);
            if (item == NULL) {
                item = Item::create(name);
                _items[name] = item;
            }
            return item;
        }
        
        Item* Inventory::put(std::string name, double count) {
            Item* item = get(name);
            if (item == NULL) {
                item = Item::create(name);
                _items[name] = item;
            }
            item->setCount(item->getCount() + count);
            return item;
        }
        
        bool Inventory::find(Item* item) {
            for (auto iter: _items) {
                if (iter.second == item) {
                    return true;
                }
            }
            return false;
        }
        
        bool Inventory::take(std::string name, double count) {
            Item* item = get(name);
            if (item != NULL) {
                if (item->getCount() >= count) {
                    item->dec(count);
                    return true;
                }
            }
            return false;
        }
        
        void Inventory::clear() {
            _items.clear();
        }
        
        bool Inventory::takeTo(std::string name, double count, Inventory* dest) {
            Item* item = get(name);
            if (item != NULL) {
                if (item->getCount() >= count) {
                    item->dec(count);
                    dest->put(name, count);
                    return true;
                }
            }
            return false;
        }
        
        double Inventory::getAttrib(std::string name) {
            double attr_val = Item::getAttrib(name);
//            for ( auto item: _items ) {
//                
//                ValueMap attribs = item.second.getAttributes();
//                for (auto attr: attribs) {
//                    std::string item_attr = toLowerCase(item.second.getName()) + "_" + attr.first;
//                    if (item_attr == name) {
//                        attr_val = attr.second.asDouble();
//                    }
//                }
//            }
            for ( auto item: _items ) {
                ValueMap modifiers = item.second->getModifiers();
                if (modifiers.find(name) != modifiers.end()) {
                    attr_val += modifiers[name].asDouble();
                }
            }
            return attr_val;
        }

        Inventory* Inventory::_DefaultInventory;
        Inventory* Inventory::_sellerInventory;
        
        Inventory* Inventory::defaultInventory() {
            if (_DefaultInventory) {
                return _DefaultInventory;
            }
            ValueMap p_vec = FileUtils::getInstance()->getValueMapFromFile("items.plist");
            _DefaultInventory = Inventory::create();
            if (_DefaultInventory) {
                for( auto iter : p_vec)
                {
                    _DefaultInventory->put(iter.first, 0);
                }
            }
            return _DefaultInventory;
        }
        
        Inventory* Inventory::sellerInventory() {
            if (_sellerInventory) {
                return _sellerInventory;
            }
            ValueMap p_vec = FileUtils::getInstance()->getValueMapFromFile("items.plist");
            _sellerInventory = Inventory::create();
            if (_sellerInventory) {
                for( auto iter : p_vec)
                {
                    bool _sellable = true;
                    ValueMap data = iter.second.asValueMap();
                    if (data.find("sellable") != data.end()) {
                        _sellable = data["sellable"].asBool();
                    }
                    if (_sellable) {
                        _sellerInventory->put(iter.first, 0);
                    }
                }
            }
            return _sellerInventory;
        }

    
        void Inventory::loadFromValueMap(ValueMap &map) {
            _items.clear();
            for (auto iter: map) {
                put(iter.first, iter.second.asFloat());
            }
        }
    
        void Inventory::saveToValueMap(ValueMap &map) {
            for (auto iter: _items) {
                if (iter.second->getCount() > 0) {
                    map[iter.first] = iter.second->getCount();
                }
            }
        }
}