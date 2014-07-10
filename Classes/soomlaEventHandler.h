//
//  soomlaEventHandler.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-3.
//
//

#ifndef __Lemonade_Jack__soomlaEventHandler__
#define __Lemonade_Jack__soomlaEventHandler__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Cocos2dxStore.h"

using namespace soomla;

#define EVENT_ON_CURRENCY_BALANCE_CHANGED "onCurrencyBalanceChanged"
#define EVENT_ON_GOOD_BALANCE_CHANGED "onGoodBalanceChanged"
#define EVENT_ON_GOOD_EQUIPPED "onGoodEquipped"
#define EVENT_ON_GOOD_UNEQUIPPED "onGoodUnEquipped"
#define EVENT_ON_GOOD_UPGRADE "onGoodUpgrade"

class GamePurchaseHandler: public CCEventHandler {
public:
    
    virtual void onBillingNotSupported();
    
    virtual void onBillingSupported();
    
    virtual void onCurrencyBalanceChanged(soomla::CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);
    
    virtual void onGoodBalanceChanged(soomla::CCVirtualGood *virtualGood, int balance, int amountAdded);
    
    virtual void onGoodEquipped(soomla::CCEquippableVG *equippableVG);
    
    virtual void onGoodUnEquipped(soomla::CCEquippableVG *equippableVG);
    
    virtual void onGoodUpgrade(soomla::CCVirtualGood *virtualGood, soomla::CCUpgradeVG *upgradeVG);
    
    virtual void onItemPurchased(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
    
    virtual void onItemPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
    
    virtual void onMarketPurchaseCancelled(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
    
    virtual void onMarketPurchase(soomla::CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *token, cocos2d::CCString *payload);
    
    virtual void onMarketPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
    
    virtual void onMarketPurchaseVerification(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
    
    virtual void onRestoreTransactionsFinished(bool success);
    
    virtual void onRestoreTransactionsStarted();
    
    virtual void onUnexpectedErrorInStore();
    
    virtual void onStoreControllerInitialized();
    
    virtual void onMarketItemsRefreshed();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    virtual void onMarketRefund(soomla::CCPurchasableVirtualItem *purchasableVirtualItem);
    virtual void onIabServiceStarted();
    virtual void onIabServiceStopped();
#endif
};

#endif
#endif /* defined(__Lemonade_Jack__soomlaEventHandler__) */
