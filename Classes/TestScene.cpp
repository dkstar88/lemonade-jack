//
//  TestScene.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-9.
//
//

#include "TestScene.h"
#include "ItemListItem.h"
#include <algorithm>
#include "Game.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* TestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestScene::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    

    auto button = Button::create("button.png");
    button->setScale9Enabled(true);
    button->setCapInsets(Rect(18, 22, 60, 22));
    button->setPosition(Point(visibleSize.width/2, visibleSize.height/2 + 200));
    button->setSize(Size(400, 100));
    button->addTouchEventListener(CC_CALLBACK_2(TestScene::touchEvent, this));
    button->setTitleText("PLAY");
    button->setTitleFontSize(56.0);
    
    this->addChild(button);

    //Init test data
    testData();

    return true;
}

void TestScene::testData() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();
    
    world = Lemonade::World::create();
    player = Lemonade::Player::create();
    auto inventory = player->getInventory();
    inventory->put("Lemon", 20);
    inventory->put("Sugar", 20);
    inventory->put("Cup", 50);
    
    listview = ItemListView::create(player);
    
    listview->setAnchorPoint(Point(0, 0));
    listview->setSize(Size(visibleSize.width, 400));
    listview->setPosition(Point(10, 0));

    this->addChild(listview);
    listview->setDirection(ScrollView::Direction::BOTH);
//    listview->setInventory(inventory);
    listview->refresh();
    
    _topBar = TopBar::create();
//    _topBar->add(inventory->get("Lemon"));
//    _topBar->add(inventory->get("Sugar"));
//    _topBar->add(inventory->get("Cup"));
//    _topBar->add(player->getMoney());
    _topBar->setPosition(Point(0, visibleSize.height-80));
//    _topBar->setSize(Size(visibleSize.width, 80));
    this->addChild(_topBar);
}

void TestScene::touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type)
{
    Item* make_target;
    std::string item_name = _PRODUCTION_->getName();
    switch (type) {
        case Widget::TouchEventType::BEGAN:
        {
            make_target = _PRODUCTION_;
//            make_target->retain();
            int max_sales = world->sales(make_target);
            
            int real_sales = player->production(item_name, max_sales);
            
            CCLOG("%s - Sales: %d/%d", item_name.c_str(), real_sales, max_sales);
            
            if (player->sale(item_name, real_sales)) {
                CCLOG("%d %s sold, money = %5.2f", real_sales, item_name.c_str(), player->getMoney()->getCount() );
            }
            listview->refresh();
            _topBar->refresh();
//            delete make_target;
//            world->incReputation(1);
            log("TOUCH_EVENT_BEGAN");
//            make_target->autorelease();
        }
            break;
        default: ;
//            break;
    }
    
}

void TestScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
