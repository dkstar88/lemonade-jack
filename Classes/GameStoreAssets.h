//
//  GameStoreAssets.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-3.
//
//

#ifndef __Lemonade_Jack__GameStoreAssets__
#define __Lemonade_Jack__GameStoreAssets__

#include "CCIStoreAssets.h"
#include "cocos2d.h"

class GameStoreAssets: public soomla::CCIStoreAssets {
    cocos2d::CCArray *mCurrencies;
    cocos2d::CCArray *mGoods;
    cocos2d::CCArray *mCurrencyPacks;
    cocos2d::CCArray *mCategories;
    cocos2d::CCArray *mNonConsumableItems;
public:
    GameStoreAssets():
    mCurrencies(NULL),
    mGoods(NULL),
    mCurrencyPacks(NULL),
    mCategories(NULL),
    mNonConsumableItems(NULL)
    {}
    
    virtual ~GameStoreAssets();
    
    static GameStoreAssets *create();
    bool init();
    
    virtual int getVersion();
    
    virtual cocos2d::CCArray *getCurrencies();
    
    virtual cocos2d::CCArray *getGoods();
    
    virtual cocos2d::CCArray *getCurrencyPacks();
    
    virtual cocos2d::CCArray *getCategories();
    
    virtual cocos2d::CCArray *getNonConsumableItems();
};

#endif /* defined(__Lemonade_Jack__GameStoreAssets__) */
