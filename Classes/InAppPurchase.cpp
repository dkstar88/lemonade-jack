//
//  InAppPurchase.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-2.
//
//

#include "InAppPurchase.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Cocos2dxStore.h"
#include "CCUIUtil.h"

using namespace soomla;

Scene* PurchaseDiamondLayer::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PurchaseDiamondLayer::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool PurchaseDiamondLayer::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 80))) {
        return false;
    }
    
    ADD_JSON_WIDGET("studio/inapp-purchase.ExportJson");

    ASSOC_TOUCHEVENT(widget, "close_button", PurchaseDiamondLayer::CloseTouchEvent);
    ASSOC_TOUCHEVENT(widget, "buy_20", PurchaseDiamondLayer::Buy20TouchEvent);
    ASSOC_TOUCHEVENT(widget, "buy_100", PurchaseDiamondLayer::Buy100TouchEvent);

    GUIUtil::SetFntToAll(widget, "fonts/marker.fnt");
    
    return true;
}

void PurchaseDiamondLayer::CloseTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    this->removeFromParentAndCleanup(true);
//    Director::getInstance()->popScene();
}

void PurchaseDiamondLayer::Buy20TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    std::string itemId = "diamond_20";
    CCSoomlaError *soomlaError = NULL;
    CCStoreInventory::sharedStoreInventory()->buyItem(itemId.c_str(), &soomlaError);
    if (soomlaError) {
        CCStoreUtils::logException("StoreBScene::onBuy", soomlaError);
        return;
    }
    
}

void PurchaseDiamondLayer::Buy100TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    std::string itemId = "diamonds_100";
    CCSoomlaError *soomlaError = NULL;
    CCStoreInventory::sharedStoreInventory()->buyItem(itemId.c_str(), &soomlaError);
    if (soomlaError) {
        CCStoreUtils::logException("StoreBScene::onBuy", soomlaError);
        return;
    }
}

#endif