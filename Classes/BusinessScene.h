//
//  BusinessLayer.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#ifndef __lemoname__BusinessLayer__
#define __lemoname__BusinessLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "ItemListView.h"
#include "TopBar.h"
#include "Car.h"
#include "PeopleSprite.h"
#include "TrafficLayer.h"
#include "Game.h"
#include "DayRecord.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class BusinessLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    CC_PROPERTY(Lemonade::World*, _world, World);
    CC_SYNTHESIZE(Lemonade::Player*, _player, Player);
    CC_SYNTHESIZE(bool, _paused, Paused);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void log(const char *format, ...);
    void initView();
    void UpdateAction(float delta);
    void UpdatePeople(float delta);
//    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void dayEnd();
    void dayStart();
    int real_sales(Player *player, Item *item);
    void speak(Sprite* sprite, std::string words);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void generatePassingPeople();
    bool tryToSellTo(PeopleSprite* people_sprite);
    // implement the "static create()" method manually
    CREATE_FUNC(BusinessLayer);
    
    bool onDaySummaryClose(Ref* pSender);
    void CloseButtonTouch(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
private:
    
    PeopleSprite* addPeople(People* people);
    
    
    float totalTime = 0;
    
    TrafficLayer *_traffics;
    
    ImageView* _background;
    Vector<PeopleSprite*> _peoples;
    ImageView *_world_icon;
    Text *_world_sign;
    Widget *car1, *car2;
    Sprite* _main_char;
    DayRecord* day_record;
    Button* closeButton;
    Text *txtConsole;
//    Text *txtTime;
    ImageView* _back;

    
};

#endif /* defined(__lemoname__BusinessLayer__) */
