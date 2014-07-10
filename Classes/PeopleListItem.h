//
//  PeopleListItem.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-21.
//
//

#ifndef __lemoname__PeopleListItem__
#define __lemoname__PeopleListItem__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "BlueButton.h"
#include "Player.h"
#include "Refreshable.h"

USING_NS_CC;
using namespace cocos2d::ui;

class PeopleListItem : public Layout, public Refreshable {
public:
    virtual bool init(Widget* content);
    virtual void refresh();
    CC_SYNTHESIZE(std::string, _people_group, PeopleGroup);
    CC_SYNTHESIZE(Lemonade::World*, _world, World);
    
    static PeopleListItem* create(Lemonade::World* world, std::string people_group, Widget* content);
    
protected:
    void TouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void advertise();
    ImageView* image;
    Text* text, *rating;
    
    Button *btnAdvert;
};



#endif /* defined(__lemoname__PeopleListItem__) */
