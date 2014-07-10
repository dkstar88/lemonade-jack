//
//  PeopleSprite.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-9.
//
//

#ifndef __teaegg__PeopleSprite__
#define __teaegg__PeopleSprite__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "People.h"
#include "Player.h"
#include "Refreshable.h"
#include "SpeechBubble.h"

USING_NS_CC;
using namespace cocos2d::ui;

class PeopleSprite : public Layout {
public:
    
    enum Direction {
        LEFT, RIGHT
    };
    enum PeopleStatus {
        Entering,
        Shopping,
        Leaving
    };
    CC_SYNTHESIZE(Lemonade::People*, _people, People);
    CC_SYNTHESIZE(PeopleStatus, _status, Status);
    CC_PROPERTY(std::string, _emotion, Emotion);
    virtual bool init(Lemonade::People *people);
    void TouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    static PeopleSprite* create(Lemonade::People *people);
    void speech(std::string text, Lemonade::Item* item);
    void money_pop(float money);
protected:
    
    Sprite* m_pSprite1;
    ImageView *_body;
    void initAnimation();
    void animFinish();
    void updateAnimation();
};
#endif /* defined(__teaegg__PeopleSprite__) */
