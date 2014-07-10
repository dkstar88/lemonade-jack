//
//  AwardsLayer.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#ifndef __teaegg__AwardsLayer__
#define __teaegg__AwardsLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "ItemListView.h"
#include "TopBar.h"

USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class AwardItem: public Layout, public Refreshable {
public:
    virtual bool init() override;
    virtual void update(float fDelta) override;
    void refresh();
//    CC_PROPERTY(Lemonade::Item*, _item, Item);
    
    CREATE_FUNC(AwardItem);
//    static AwardItem* create(Widget *content, Lemonade::Item* item);
    void setLayout(Widget *content);
    void buyTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    
private:
    ImageView *icon;
    Text *name, *desc, *price, *count;
    Button *buyOne, *buyTen;
};

class AwardsLayer : public cocos2d::Layer, public Refreshable
{
public:
    virtual bool init() override;
    void UpdateUI(float delta);
    void refresh();
    CREATE_FUNC(AwardsLayer);
//    ShopListItem* find(Lemonade::Item* item);
private:
    ListView* listview;
    Layout* item_template;
};


#endif /* defined(__teaegg__AwardsLayer__) */
