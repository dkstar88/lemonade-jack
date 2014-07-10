//
//  PeopleInfoLayer.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-21.
//
//

#ifndef __lemoname__PeopleInfoLayer__
#define __lemoname__PeopleInfoLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "RefreshListView.h"
#include "GameVars.h"
//#include "TopBar.h"

USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class PeopleInfoLayer : public cocos2d::Layer, public Refreshable {
public:
    virtual bool init() override;
    void refresh() override {
        //setWorld(_PLAYER_->getActiveWorld());
        for (auto item: listview->getItems()) {
            if (Refreshable* ref = dynamic_cast<Refreshable*>(item)) {
                ref->refresh();
            }
        }
    }
    CC_PROPERTY(Lemonade::World*, _world, World);
    void TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    CREATE_FUNC(PeopleInfoLayer);

protected:

    std::map<Ref*, World*> worldButtonMap;
    ListView *listview;
    Layout* worldList;
    Widget* worldButtonTemplate;
    Widget* listitem;
//    ImageView* image;
//    Text *title, *desc;
    
    
};

#endif /* defined(__lemoname__PeopleInfoLayer__) */
