//
//  InAppPurchase.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-2.
//
//

#ifndef __Lemonade_Jack__InAppPurchase__
#define __Lemonade_Jack__InAppPurchase__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ui/CocosGUI.h"
#include "Lemonade.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class PurchaseDiamondLayer: public LayerColor {
public:
    static Scene* createScene();
    bool init() override;
    
    void CloseTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void Buy20TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void Buy100TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    CREATE_FUNC(PurchaseDiamondLayer);
};


#endif /* defined(__Lemonade_Jack__InAppPurchase__) */
#endif