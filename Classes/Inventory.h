//
//  Inventory.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#ifndef __lemoname__Inventory__
#define __lemoname__Inventory__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include <map>

USING_NS_CC;


namespace Lemonade {

        typedef std::map<std::string, Item*> ItemDict;
        typedef std::map<std::string, double> ItemsCount;
        class Inventory {
        public:
            virtual bool init();
            Item* get(std::string name);
            Item* get(std::string name, bool forceCreate);
            Item* put(std::string name);
            Item* put(std::string name, double count);
            bool take(std::string name, double count);
            bool find(Item* item);
            double getAttrib(std::string name);
            void clear();
            bool takeTo(std::string name, double count, Inventory* dest);
            
            CC_SYNTHESIZE(ItemDict, _items, Items);
            CC_SYNTHESIZE(double, _count, Count); // Name, e.g. Lemon
            
            virtual std::string getDescription() const;
            
            void loadFromValueMap(ValueMap &map);
            void saveToValueMap(ValueMap &map);
            
            static Inventory* create()
            {
                Inventory *pRet = new Inventory();
                if (pRet && pRet->init())
                {
                    return pRet;
                }
                else
                {
                    delete pRet;
                    pRet = NULL;
                    return pRet;
                }
            }
            
            static Inventory* defaultInventory();
            static Inventory* sellerInventory();
//
        protected:
            static Inventory* _DefaultInventory;
            static Inventory* _sellerInventory;
        };

}

#endif /* defined(__lemoname__Inventory__) */
