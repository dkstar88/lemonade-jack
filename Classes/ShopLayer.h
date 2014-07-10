//
//  ShopLayer.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#ifndef __lemoname__ShopLayer__
#define __lemoname__ShopLayer__

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

class ShopListItem: public Layout, public Refreshable {
public:
    virtual bool init() override;
    virtual void update(float fDelta) override;
    void refresh();
    CC_PROPERTY(Lemonade::Item*, _item, Item);
    
    CREATE_FUNC(ShopListItem);
    static ShopListItem* create(Widget *content, Lemonade::Item* item);
    void setLayout(Widget *content);
    void buyTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    
private:
    ImageView *icon;
    Text *name, *desc, *price, *count;
    Button *buyOne, *buyTen;
};

class ShopLayer : public cocos2d::Layer, public Refreshable
{
public:
    virtual bool init() override;
    void UpdateUI(float delta);
    void refresh();
    CREATE_FUNC(ShopLayer);
    ShopListItem* find(Lemonade::Item* item);
private:
    ListView* listview;
    Layout* item_template;
};

#endif /* defined(__lemoname__ShopLayer__) */
