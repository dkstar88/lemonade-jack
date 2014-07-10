//
//  ItemListItem.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#ifndef __lemoname__ItemListItem__
#define __lemoname__ItemListItem__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "BlueButton.h"
#include "Player.h"
#include "Refreshable.h"

USING_NS_CC;
using namespace cocos2d::ui;

class ItemListItem : public Layout, public Refreshable {
public:
    virtual bool init() override;
    virtual void update(float delta) override;
    virtual void refresh() override;
    CC_PROPERTY(Lemonade::Item*, _item, Item);
    
    static ItemListItem* create(Lemonade::Item* item_);

protected:
    ImageView* image;
    Text* text;
};

class ItemListItemBuy: public ItemListItem {
public:
    virtual bool init() override;
    virtual void refresh() override;
    void buy(int sales);
    bool canBuy(int sales);
    
    CC_PROPERTY(bool, _showBuyOne, ShowBuyOne);
    CC_PROPERTY(bool, _showBuyTen, ShowBuyTen);
    CC_SYNTHESIZE(Lemonade::Player*, _player, Player);
    
    static ItemListItemBuy* create(Lemonade::Item* item_);
    
protected:
    void buyTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
//    void buyTenTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    BlueButton *_buyOne, *_buyTen;
    
};

#endif /* defined(__lemoname__ItemListItem__) */
