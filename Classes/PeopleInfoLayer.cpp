//
//  PeopleInfoLayer.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-21.
//
//

#include "PeopleInfoLayer.h"
#include "PeopleListItem.h"
#include "GameVars.h"
#include "Player.h"
#include "World.h"

bool PeopleInfoLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    ADD_JSON_WIDGET("studio/people_info.ExportJson");
    Size sz = Director::getInstance()->getVisibleSize();
    auto content = SEEK_WIDGET(Widget*, widget, "content");
    content->setSize(Size(sz.width, sz.height-200));
    content->setPosition(Point(0, 80));
    
    worldButtonTemplate = SEEK_WIDGET(Widget*, widget, "world_item");
    worldButtonTemplate->setVisible(false);
    worldButtonTemplate->retain();
    
    worldList = SEEK_WIDGET(Layout*, widget, "world_list");
    worldList->removeAllChildren();
    worldList->setPosition(Point(0, sz.height-150));
    Universe universe = _PLAYER_->getUniverse();
    worldButtonMap.clear();
    for(auto world: universe) {
        Widget *worldbutton = worldButtonTemplate->clone();
        worldbutton->setVisible(true);
        
        Button* btn = SEEK_WIDGET(Button*, worldbutton, "world_button");
        btn->setTitleText(world->getName());
        btn->addTouchEventListener(CC_CALLBACK_2(PeopleInfoLayer::TouchEvent, this));
        worldButtonMap[btn] = world;
        worldList->addChild(worldbutton);
    }
    
    listitem = SEEK_WIDGET(Widget*, widget, "listitem");
    listitem->setVisible(false);
    listitem->retain();
    listview = SEEK_WIDGET(ListView*, widget, "listview");
    listview->removeAllItems();
    listview->setDirection(ScrollView::Direction::VERTICAL);
//    setWorld(_PLAYER_->getActiveWorld());
    //    listview->setInventory(inventory);
//    listview->refresh();
    setWorld(*universe.begin());
    return true;
    
}

void PeopleInfoLayer::setWorld(Lemonade::World* val) {
    if (_world == val) {
        return;
    }
    _world = val;
    if (_world) {
        listview->removeAllItems();
        std::vector<std::string> groups = _world->getPeople()->getGroupsByPop();
        for (std::string ppl_group: groups) {
//            People *pp = Lemonade::People::create(ppl_group);
            auto item = PeopleListItem::create(_world, ppl_group, listitem->clone());
            listview->pushBackCustomItem(item);
        }
//        listview->refresh();
//        image->loadTexture(_world->getIcon());
//        title->setText(_world->getName());
//        desc->setText(_world->getDesc());
        //        _back->loadTexture(_world->getIcon());
        //        _back->setScale(5);
    }
}

void PeopleInfoLayer::TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    World* world = worldButtonMap[pSender];
    setWorld(world);
    refresh();
}

Lemonade::World* PeopleInfoLayer::getWorld() {
    return _world;
}