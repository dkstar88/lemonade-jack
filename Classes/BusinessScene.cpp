//
//  BusinessLayer.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#include "BusinessScene.h"
#include "ItemListItem.h"
#include "MenuScene.h"
#include "GameScene.h"
#include <algorithm>
#include "GameVars.h"
#include <time.h>
#include "DaySummary.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DIAAchievement.h"
#endif


USING_NS_CC;
using namespace cocos2d::ui;

const float ACTION_INTERVAL = 0.5;
#define DAY_START (3600*8)
#define DAY_END (3600*18)
#define TIME_RATIO (3600/6)
const float REPUTATION_GAIN = 10.0f;
const float REPUTATION_LOSE = 5.0;

Scene* BusinessLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BusinessLayer::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BusinessLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _paused = true;
    _player = _PLAYER_;
    
    

    //Init test data
    initView();
    setWorld(_player->getActiveWorld());
    dayStart();
    
    return true;
}

void BusinessLayer::log(const char *format, ...)
{
    
//    va_list args;
//    va_start(args, format);
//    CCLOG(format, args);
////    CCLOG(format, args);
//    
//    char buf[MAX_LOG_LENGTH];
//    
//    vsnprintf(buf, MAX_LOG_LENGTH-3, format, args);
//    strcat(buf, "\n");
//    std::string newText = txtConsole->getString() + buf;
//    txtConsole->setString(newText);
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    txtConsole->setSize(Size(visibleSize.width, txtConsole->getContentSize().height));
//    
//    va_end(args);
}

int BusinessLayer::real_sales(Player *player, Item *item) {
//    int forseen_sales = _world->sales(item)/24;
    
//    int r = CCRANDOM_0_1() * 100;
//    if ( r >= 50) {
//        return 0;
//    }
    
    int real_sales = 0;

    auto pp = _world->getRandomPeople();
    auto people_sprite = addPeople(pp);
    TasteResult* taste_result = pp->demand(item);
    int demand = taste_result->getDemand();
        if (demand > 0) {
            // sale
            std::string item_name = item->getName();
            if (player->production(item_name, demand) && player->canSale(item_name, demand)) {
                player->sale(item_name, demand);
//                pp->setMoney( pp->getMoney() - item->getPrice());
                pp->IncRep( REPUTATION_GAIN );
                real_sales++;

				people_sprite->speech(StringUtils::format("Bought %d", demand), item);
//                log("%d %s sold to %s, money = %5.2f", demand, item_name.c_str(), pp->getName().c_str(), _player->getMoney()->getCount() );
            } else {
                people_sprite->speech("Out of stock!", item);
//                log("%s wants to buy %d %s, But you are out of ingredient", pp->getName().c_str(), demand, item_name.c_str(), _player->getMoney()->getCount() );
                pp->IncRep(-REPUTATION_LOSE);
            }
        } else {

            people_sprite->speech(taste_result->getMessage(), item);
//            log("Failed to sale to %s, demand to low", pp->getName().c_str());
            // People do not demand, but slightly increase reputation
//            pp->IncRep(2);
        }

    return real_sales;
}

void BusinessLayer::generatePassingPeople() {
    auto pp = _world->getRandomPeople();
    addPeople(pp);

}

void BusinessLayer::UpdateAction(float delta) {
    if (_world && (!_paused)) {

        // Generate passing people
        generatePassingPeople();
        
        UpdatePeople(delta);

        totalTime += delta;
        time_t time = (totalTime) * TIME_RATIO * _GAME_.getSpeed() + DAY_START;
        _player->setTime(time);
        
        if (time > DAY_END) {
            dayEnd();
        }
    }
}

void BusinessLayer::dayStart() {
    totalTime = 0;
    day_record = DayRecords::getDayRecord(_PLAYER_->getDay());
    _paused = false;
    
    for (auto c: _peoples) {
        removeChild(c);
    }
    _peoples.clear();
    _traffics->restart();
    schedule(schedule_selector(BusinessLayer::UpdateAction), ACTION_INTERVAL, kRepeatForever, 0);
    
}

PeopleSprite* BusinessLayer::addPeople(People* people) {
    
    float appear_rate = CCRANDOM_0_1() * _world->getPopulation() / 1500;
    
    if (appear_rate < 0.5) {
        return NULL;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (auto ps: _peoples) {
        Point pos = ps->getPosition();

        if (pos.x > visibleSize.width-40) {
            return NULL;
        }
        
    }
    
    auto ps = PeopleSprite::create(people);
    _peoples.pushBack(ps);
    addChild(ps);
    return ps;
}

bool BusinessLayer::tryToSellTo(PeopleSprite* people_sprite) {
    int real_sales = 0;

    auto pp = people_sprite->getPeople();
    TasteResult* taste_result = pp->demand(_PRODUCTION_);
    if (!taste_result) {
        return false;
    }
    int demand = taste_result->getDemand();

	//int demand = 1;
    if (demand > 0) {
        // sale
        std::string item_name = _PRODUCTION_->getName();
        if (_player->production(item_name, demand) && _player->canSale(item_name, demand)) {
            _player->sale(item_name, demand);
//            pp->setMoney( pp->getMoney() - _PRODUCTION_->getPrice());
            pp->IncRep( REPUTATION_GAIN );
            real_sales++;
            
            people_sprite->speech(StringUtils::format("Bought %d", demand), _PRODUCTION_);
            people_sprite->setEmotion("happy");
            return true;
            //                log("%d %s sold to %s, money = %5.2f", demand, item_name.c_str(), pp->getName().c_str(), _player->getMoney()->getCount() );
        } else {
            people_sprite->speech("Out of stock!", _PRODUCTION_);
            //                log("%s wants to buy %d %s, But you are out of ingredient", pp->getName().c_str(), demand, item_name.c_str(), _player->getMoney()->getCount() );
            pp->IncRep(-REPUTATION_LOSE);
            
        }
    } else {
        people_sprite->setEmotion("angry");
        CCLOG("%s Taste: %s", _PRODUCTION_->getName().c_str(), _PRODUCTION_->getTaste()->getDescription().c_str());
        CCLOG("%s Taste: %s", pp->getName().c_str(), pp->getTaste()->getDescription().c_str());

        if (taste_result->getMessage().size())
            people_sprite->speech(taste_result->getMessage(), _PRODUCTION_);

    }
    return false;
}

void BusinessLayer::UpdatePeople(float delta) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
	std::vector<PeopleSprite*> deletelist;
    for (auto ps: _peoples) {
        Point pos = ps->getPosition();
        if (ps->getStatus() == PeopleSprite::PeopleStatus::Entering) {
            if (pos.x < visibleSize.width/2) {
                ps->setStatus(PeopleSprite::PeopleStatus::Shopping);
            }
        } else if (ps->getStatus() == PeopleSprite::PeopleStatus::Shopping) {
            tryToSellTo(ps);
            ps->setStatus(PeopleSprite::PeopleStatus::Leaving);
        }
        
        if (ps->getStatus()==PeopleSprite::PeopleStatus::Leaving && !ps->isVisible()) {
			deletelist.push_back(ps);
        }
        
    }

	for (auto ps : deletelist) {
		_peoples.eraseObject(ps);
		removeChild(ps);
	}


}

void BusinessLayer::dayEnd() {
    unschedule(schedule_selector(BusinessLayer::UpdateAction));
    _paused = true;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sGameCenter->postScore("top_earner", day_record->getEarned());
    sGameCenter->postScore("top_seller", day_record->getSoldItems().size());
//    sGameCenter->postScore("top_earner", day_record->getEarned());
    /*
     Check achievements
     */
    
    if (day_record->getEarned() >= 100) {
        sGameCenter->unlockAchievement(business_level);
    }
    
    if (day_record->getEarned() >= 500) {
        sGameCenter->unlockAchievement(business_level_2);
    }
    
    if (_world->getReputation() >= 10) {
        sGameCenter->unlockAchievement(rep_10);
    }
    
    if (_world->getReputation() >= 20) {
        sGameCenter->unlockAchievement(rep_10);
    }
#endif
    
    // Serialize Day Records to file
    DayRecords::setDayRecord(_player->getDay(), *day_record);
    
    _player->incDay();
    
    for (auto c: _peoples) {
        removeChild(c);
    }
    _peoples.clear();
    
    auto summaryDialog = DaySummaryLayer::create(day_record);
    summaryDialog->onClose = CC_CALLBACK_1(BusinessLayer::onDaySummaryClose, this);
    addChild(summaryDialog, 10);
    
}

bool BusinessLayer::onDaySummaryClose(Ref* pSender) {
    Director::getInstance()->popScene();
    return true;
}

void BusinessLayer::initView() {
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto _top_bar_layer = TopBarLayer::create();
    addChild(_top_bar_layer, 5);
//    Point origin = Director::getInstance()->getVisibleOrigin();
    
    ADD_JSON_WIDGET("studio/business.ExportJson");
    
    _background = SEEK_WIDGET(ImageView*, widget, "building");
//    _background->loadTexture("building-backdrop.png");
    _background->setPosition(Point(0, 0));
    auto _road = SEEK_WIDGET(ImageView*, widget, "road");
    _road->setVisible(false);
//    _road->loadTexture("street.png");
    _road->setPosition(Point(0, 0));
    
    auto _pavement = SEEK_WIDGET(ImageView*, widget, "pavement");
//    _pavement->loadTexture("pavement.png");
    _pavement->setPosition(Point(0, 100));
    _pavement->setVisible(false);
//    _world_icon = SEEK_WIDGET(ImageView*, widget, "world_icon");
//    _world_icon->setVisible(false);
    _world_sign = SEEK_WIDGET(Text*, widget, "world_name");
    
    
    auto _stand = SEEK_WIDGET(ImageView*, widget, "stand");
    

    auto layout = _stand->getLayoutParameter(LayoutParameter::Type::RELATIVE);
//    layout->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
    layout->setMargin(Margin(0, 0, 0, 150));
    _stand->setLayoutParameter(layout);
//    _stand->setAnchorPoint(Point(0.5, 0));
//    _stand->setPosition(Point(0, 160));
    
    _traffics = TrafficLayer::create();
    _traffics->setLocalZOrder(10);
    addChild(_traffics);

    // Fix close button z-order (under cars)
    closeButton = SEEK_WIDGET(Button*, widget, "back_button");
    closeButton->retain();
    closeButton->getParent()->removeChild(closeButton);
    closeButton->setLocalZOrder(40);
    closeButton->addTouchEventListener(CC_CALLBACK_2(BusinessLayer::CloseButtonTouch, this));
    addChild(closeButton);
//    
//    txtConsole = Text::create();
//    txtConsole->setFontSize(20);
//    txtConsole->setColor(Color3B(0, 0, 0));
//    txtConsole->setPosition(Point(10, 0));
//    txtConsole->setSize(Size(visibleSize.width-40, visibleSize.height-420));
//    txtConsole->setAnchorPoint(Point(0, 0));
//    txtConsole->setTextHorizontalAlignment(TextHAlignment::LEFT);
//    txtConsole->retain();
////    txtConsole->setOpacity(2);
//    
//    auto scroller = ScrollView::create();
//    scroller->setSize(Size(visibleSize.width-20, visibleSize.height-400));
//    scroller->setAnchorPoint(Point(0, 0));
//    scroller->addChild(txtConsole);
//    scroller->setBackGroundImage("dark-well.png");
//    scroller->setBackGroundImageCapInsets(Rect(22, 22, 60, 60));
//    scroller->setBackGroundImageOpacity(100);
//    scroller->setBackGroundImageScale9Enabled(true);
//    scroller->setPosition(Point(10, 300));
////    scroller->setOpacity(0.2);
//    addChild(scroller);
    

    auto inventory = _player->getInventory();
    inventory->put("Lemon", 0);
    inventory->put("Sugar", 0);
    inventory->put("Cup", 0);
    
//    _main_char = Sprite::create("businessman");
//    _main_char->setPosition(visibleSize.width/2, visibleSize.height/2);
//    addChild(_main_char);
}

void BusinessLayer::CloseButtonTouch(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) dayEnd();
}


void BusinessLayer::setWorld(Lemonade::World* val) {
    _world = val;
    if (_world) {
        std::string worldbackground = toLowerCase(StringUtils::format("worlds/background/%s.png", _world->getName().c_str()));
//
        _background->loadTexture(worldbackground);
////        _world_icon->loadTexture(_world->getImage());
        _world_sign->setString(_world->getName());

        std::string background_music = "sfx/Get You Groove On.mp3";
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(background_music.c_str(), true);
    }
}

void BusinessLayer::speak(Sprite* sprite, std::string words) {
    Point p = sprite->getPosition();
    p.y += sprite->getContentSize().height;
    // TODO: Add speech bubble 
}


Lemonade::World* BusinessLayer::getWorld() {
    return _world;
}

void BusinessLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene( TransitionJumpZoom::create(0.5, MenuScene::createScene()));
}
