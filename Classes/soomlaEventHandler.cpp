//
//  soomlaEventHandler.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-3.
//
//

#include "soomlaEventHandler.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "GameVars.h"

#include "Cocos2dxStore.h"
#include "cocos2d.h"
#include "AlertDialog.h"

#define TAG "GamePurchaseHandler >>>"

USING_NS_CC;

void GamePurchaseHandler::onBillingNotSupported() {
    soomla::CCStoreUtils::logDebug(TAG, "BillingNotSupported");
}

void GamePurchaseHandler::onBillingSupported() {
    soomla::CCStoreUtils::logDebug(TAG, "BillingSupported");
}

void GamePurchaseHandler::onCurrencyBalanceChanged(soomla::CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
    soomla::CCStoreUtils::logDebug(TAG, "CurrencyBalanceChanged");
    CCNotificationCenter::sharedNotificationCenter()->postNotification
    (EVENT_ON_CURRENCY_BALANCE_CHANGED, CCInteger::create(balance));
}

void GamePurchaseHandler::onGoodBalanceChanged(soomla::CCVirtualGood *virtualGood, int balance, int amountAdded) {
    soomla::CCStoreUtils::logDebug(TAG, "GoodBalanceChanged");
    CCNotificationCenter::sharedNotificationCenter()->postNotification
    (EVENT_ON_GOOD_BALANCE_CHANGED, CCArray::create(virtualGood, CCInteger::create(balance), NULL));
}

void GamePurchaseHandler::onGoodEquipped(soomla::CCEquippableVG *equippableVG) {
    soomla::CCStoreUtils::logDebug(TAG, "GoodEquipped");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_ON_GOOD_EQUIPPED, equippableVG);
}

void GamePurchaseHandler::onGoodUnEquipped(soomla::CCEquippableVG *equippableVG) {
    soomla::CCStoreUtils::logDebug(TAG, "GoodUnEquipped");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_ON_GOOD_UNEQUIPPED, equippableVG);
}

void GamePurchaseHandler::onGoodUpgrade(soomla::CCVirtualGood *virtualGood, soomla::CCUpgradeVG *upgradeVG) {
    soomla::CCStoreUtils::logDebug(TAG, "GoodUpgrade");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_ON_GOOD_UPGRADE, virtualGood);
}

//void GamePurchaseHandler::onItemPurchased(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
//    soomla::CCStoreUtils::logDebug(TAG, "ItemPurchased");
//}
//
//void GamePurchaseHandler::onItemPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
//    soomla::CCStoreUtils::logDebug(TAG, "ItemPurchaseStarted");
//}

void GamePurchaseHandler::onMarketPurchaseCancelled(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
//    AlertDialog::Alert("Game Store", StringUtils::format("Your purchase of [%s] has been cancelled.", purchasableVirtualItem->getName()->getCString()));
    soomla::CCStoreUtils::logDebug(TAG, "MarketPurchaseCancelled");
}

void GamePurchaseHandler::onMarketPurchase(soomla::CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *token, cocos2d::CCString *payload) {
    soomla::CCStoreUtils::logDebug(TAG, "MarketPurchase");
}

void GamePurchaseHandler::onMarketPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCStoreUtils::logDebug(TAG, "MarketPurchaseStarted");
}

void GamePurchaseHandler::onMarketPurchaseVerification(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCStoreUtils::logDebug(TAG, "MarketPurchaseVerification");
}

void GamePurchaseHandler::onRestoreTransactionsFinished(bool success) {
    soomla::CCStoreUtils::logDebug(TAG, "RestoreTransactions");
}

void GamePurchaseHandler::onRestoreTransactionsStarted() {
    soomla::CCStoreUtils::logDebug(TAG, "RestoreTransactionsStarted");
}

void GamePurchaseHandler::onUnexpectedErrorInStore() {
    soomla::CCStoreUtils::logDebug(TAG, "UnexpectedErrorInStore");
}

void GamePurchaseHandler::onStoreControllerInitialized() {
    soomla::CCStoreUtils::logDebug(TAG, "StoreContorllerInitialized");
}

void GamePurchaseHandler::onMarketItemsRefreshed() {
    
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

void GamePurchaseHandler::onMarketRefund(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCStoreUtils::logDebug(TAG, "MarketRefund");
}

void GamePurchaseHandler::onIabServiceStarted() {
    soomla::CCStoreUtils::logDebug(TAG, "IabServiceStarted");
}

void GamePurchaseHandler::onIabServiceStopped() {
    soomla::CCStoreUtils::logDebug(TAG, "IabServiceStopped");
}
#endif

void GamePurchaseHandler::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem) {
    auto itemId = purchasableVirtualItem->getItemId();
    CCLOG("ItemPurchased: %s", purchasableVirtualItem->getItemId());
    if (itemId->compare("diamond_20") == 0) {
        AlertDialog::Alert("Game Store", "You have received 20 diamonds.");
        _PLAYER_->incDiamond(20);
        
    } else if (itemId->compare("diamonds_100") == 0) {
        AlertDialog::Alert("Game Store", "You have received 100 diamonds.");
        _PLAYER_->incDiamond(100);
    }
    GlobalVars::SaveGame();
    soomla::CCStoreUtils::logDebug(TAG, "ItemPurchased");
}

void GamePurchaseHandler::onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
    CCLOG("ItemPurchaseStarted: %s", purchasableVirtualItem->getItemId());
}

#endif