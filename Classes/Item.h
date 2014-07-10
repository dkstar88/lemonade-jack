//
//  Item.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-9.
//
//

#ifndef __lemoname__Item__
#define __lemoname__Item__

#include "cocos2d.h"
#include "stdutil.h"
#include "Taste.h"
#include "Recipe.h"

USING_NS_CC;

namespace Lemonade {
    
    class Item {
    public:
        
		Item();
		virtual ~Item();

        virtual bool init();
        bool initWithName(std::string name);
        bool setItemName(std::string name);
        CC_SYNTHESIZE(std::string, _name, Name); // Name, e.g. Lemon
        CC_SYNTHESIZE(std::string, _desc, Desc);
        CC_SYNTHESIZE(std::string, _icon, Icon); // Icon Path
        CC_PROPERTY(double, _price, Price); // item price e.g. $0.5
        CC_SYNTHESIZE(double, _price_var, PriceVar); // Price Variation +-0.2
        CC_SYNTHESIZE(int, _shelf_life, ShelfLife); // Expire time in days
        //CC_SYNTHESIZE(double, _weight, Weight);
        CC_SYNTHESIZE(double, _space, Space);
        CC_SYNTHESIZE(double, _demand, Demand);
        CC_SYNTHESIZE(Recipe*, _recipe, Recipe);
        CC_SYNTHESIZE(ValueMap, _modifiers, Modifiers);
        CC_SYNTHESIZE(ValueMap, _attributes, Attributes);
        CC_SYNTHESIZE(double, _count, Count);
        CC_SYNTHESIZE(bool, _sellable, Sellable);
        CC_PROPERTY(Lemonade::Taste*, _taste, Taste);
        CC_SYNTHESIZE(int, _sold, Sold);
        
        virtual std::string getDescription() const;
        
        void loadFromValueMap(ValueMap &map);
        void saveToValueMap(ValueMap &map);
        
        double inc(double val);
        double dec(double val);
        
        static double getAttrib(std::string item_attrib_name);
        static Item* create(std::string name, std::string icon, double price, double price_var, int shelf_life, double demand);
        static Item* create(std::string name);

    };
    
}

#endif /* defined(__lemoname__Item__) */
