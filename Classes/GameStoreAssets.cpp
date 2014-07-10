//
//  GameStoreAssets.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-3.
//
//

#include "GameStoreAssets.h"

#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCVirtualGood.h"
#include "CCSingleUseVG.h"
#include "CCPurchaseWithMarket.h"
#include "CCPurchaseWithVirtualItem.h"
#include "CCVirtualCategory.h"
#include "CCNonConsumableItem.h"
#include "CCUpgradeVG.h"
#include "CCSingleUsePackVG.h"
#include "CCEquippableVG.h"

USING_NS_CC;
using namespace soomla;

#define CURRENCY_ITEM_ID "diamond"
#define DIAMOND_PACK20_PRODUCT_ID "diamond_20"
#define DIAMOND_PACK100_PRODUCT_ID "diamonds_100"

GameStoreAssets *GameStoreAssets::create() {
    GameStoreAssets *ret = new GameStoreAssets();
    ret->autorelease();
    ret->init();
    
    return ret;
}

bool GameStoreAssets::init() {
    /** Virtual Currencies **/
    CCVirtualCurrency *diamondCurrency = CCVirtualCurrency::create(
                                                                  CCString::create("Diamonds"),
                                                                  CCString::create(""),
                                                                  CCString::create(CURRENCY_ITEM_ID)
                                                                  );
    
    CCVirtualCurrencyPack *diamond20Pack = CCVirtualCurrencyPack::create(
                                                                                                        CCString::create("20 Diamonds"), // name
                                                                                                        CCString::create("20 Diamonds"), // description
                                                                                                        CCString::create("diamond_20"), // item id
                                                                                                        CCInteger::create(20),	// number of currencies in the pack
                                                                                                        CCString::create(CURRENCY_ITEM_ID), // the currency associated with this pack
                                                                                                        CCPurchaseWithMarket::create(CCString::create(DIAMOND_PACK20_PRODUCT_ID), CCDouble::create(4.99))
                                                                                                        );
    
    CCVirtualCurrencyPack *diamond100Pack = CCVirtualCurrencyPack::create(
                                                                         CCString::create("100 Diamonds"), // name
                                                                         CCString::create("100 Diamonds"), // description
                                                                         CCString::create("diamonds_100"), // item id
                                                                         CCInteger::create(100),	// number of currencies in the pack
                                                                         CCString::create(CURRENCY_ITEM_ID), // the currency associated with this pack
                                                                         CCPurchaseWithMarket::create(CCString::create(DIAMOND_PACK100_PRODUCT_ID), CCDouble::create(9.99))
                                                                         );
    /** Google MANAGED Items **/
//    
//    CCNonConsumableItem *noAdsNoncons = CCNonConsumableItem::create(
//                                                                    CCString::create("No Ads"),
//                                                                    CCString::create("Test purchase of MANAGED item."),
//                                                                    CCString::create("no_ads"),
//                                                                    CCPurchaseWithMarket::createWithMarketItem(CCMarketItem::create(
//                                                                                                                                    CCString::create(NO_ADDS_NONCONS_PRODUCT_ID),
//                                                                                                                                    CCInteger::create(CCMarketItem::NONCONSUMABLE), CCDouble::create(1.99))
//                                                                                                               )
//                                                                    );
    
    mCurrencies = CCArray::create(diamondCurrency, NULL);
    mCurrencies->retain();
    
    mGoods = CCArray::create();
    mGoods->retain();
    
    mCurrencyPacks = CCArray::create(diamond20Pack, diamond100Pack, NULL);
    mCurrencyPacks->retain();
    
    mCategories = CCArray::create();
    mCategories->retain();
    
    mNonConsumableItems = CCArray::create();
    mNonConsumableItems->retain();
    
    return true;
}

GameStoreAssets::~GameStoreAssets() {
    CC_SAFE_RELEASE(mCurrencies);
    CC_SAFE_RELEASE(mGoods);
    CC_SAFE_RELEASE(mCurrencyPacks);
    CC_SAFE_RELEASE(mCategories);
    CC_SAFE_RELEASE(mNonConsumableItems);
}

int GameStoreAssets::getVersion() {
    return 0;
}

cocos2d::CCArray *GameStoreAssets::getCurrencies() {
    return mCurrencies;
}

cocos2d::CCArray *GameStoreAssets::getGoods() {
    return mGoods;
}

cocos2d::CCArray *GameStoreAssets::getCurrencyPacks() {
    return mCurrencyPacks;
}

cocos2d::CCArray *GameStoreAssets::getCategories() {
    return mCategories;
}

cocos2d::CCArray *GameStoreAssets::getNonConsumableItems() {
    return mNonConsumableItems;
}