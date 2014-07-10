//
//  PeopleListItem.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-21.
//
//

#include "PeopleListItem.h"
#include <stdio.h>
#include "GameVars.h"

using namespace StringUtils;

bool PeopleListItem::init(Widget* content) {
    if (!Layout::init()) {
        return false;
    }
    content->setVisible(true);
    content->setPosition(Point(0, 0));
    addChild(content);
    setSize(Size(900, 64));
    image = SEEK_WIDGET(ImageView*, content, "icon");
    text = SEEK_WIDGET(Text*, content, "group_name");
    rating = SEEK_WIDGET(Text*, content, "rating");
    ASSOC_BUTTON(btnAdvert, content, "btn_advert", PeopleListItem::TouchEvent);
    btnAdvert->setTitleColor(Color3B(33, 33, 33));
    return true;
}

void PeopleListItem::refresh() {
    if (_world && _people_group.size()) {
        
        
        Lemonade::PeopleList* people_list = _world->getPeople();
        Lemonade::PeopleGroup* pp = people_list->getGroup(_people_group);
        // Get people group average reputation
        image->loadTexture(pp->getIcon());
        int pop = people_list->getGroup(_people_group)->getDistribution()*people_list->getPopulation();
        text->setString(format("%s (pop: %d)", pp->getName().c_str(), pop));
        rating->setString(format("%d%%", pp->getReputation()));
    }
}

void PeopleListItem::advertise() {
    // Takes 2 diamond
    
        if (_PLAYER_->incDiamond(-2)) {
            //_PLAYER_->getDiamond()->setCount( (int)_PLAYER_->getDiamond()->getCount()-2 );
            // Increase reputation by 10
            _world->getPeople()->incGroupRep(_people_group, 10);
        }

}

void PeopleListItem::TouchEvent(cocos2d::Ref *pSender, TouchEventType type) {
    if (type==TouchEventType::BEGAN) {
        if (pSender == btnAdvert) {
            // TODO::Advertising
            advertise();
        }
    }
}

PeopleListItem* PeopleListItem::create(Lemonade::World* world, std::string people_group, Widget* content) {
    PeopleListItem* res = new PeopleListItem();
    if (res->init(content)) {
        res->setWorld(world);
        res->setPeopleGroup(people_group);
        res->refresh();
        return res;
    } else {
        return NULL;
    }
    
}