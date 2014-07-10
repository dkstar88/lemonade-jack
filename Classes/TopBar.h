//
//  TopBar.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-18.
//
//

#ifndef __lemoname__TopBar__
#define __lemoname__TopBar__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "ItemListItem.h"
#include "Player.h"

USING_NS_CC;
using namespace cocos2d::ui;

class TopBar : public Layout {
    
public:
    virtual bool init() override;
    CC_SYNTHESIZE(Lemonade::Player*, _player, Player);
    void refresh();
    void UpdateUI(float delta);

    CREATE_FUNC(TopBar);
    
    
private:
    void AddMoneyTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void AddDiamondTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void ChangeSpeedTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    
    Text *txtDay, *txtTime;
    TextBMFont *txtMoney, *txtReputation, *txtDiamond, *txtSpeed;

};

#endif /* defined(__lemoname__TopBar__) */
