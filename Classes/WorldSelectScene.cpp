//
//  WorldSelectScene.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#include "WorldSelectScene.h"
#include "GameScene.h"
#include "GameVars.h"
#include "ValueMapMacros.h"
#include "BusinessScene.h"

//#ifdef DEBUG
#include "Util.h"
//#endif


USING_NS_CC;
using namespace cocos2d::ui;
using namespace StringUtils;

bool WorldButton::init(World* world, Widget* content) {
    if (!Layout::init()) {
        return false;
    }
    
    this->addChild(content);
    content->setVisible(true);
    content->setPosition(Point(0, 0));
    _content = content;
    _playbutton = SEEK_WIDGET(Button*, content, "play_button");
//    assert(_playbutton);
    if (_playbutton) {
        _playbutton->addTouchEventListener(CC_CALLBACK_2(WorldButton::playTouchEvent, this));
        _playbutton->setLocalZOrder(10);
        _playbutton->retain();
        content->removeChild(_playbutton);
    }
    _rating = SEEK_WIDGET(Text*, content, "reputation");
    _rating->setString(format("%d", (int)world->getReputation()));
    auto price = Helper::seekWidgetByName(content, "price");
    _price = dynamic_cast<TextBMFont*>(price);
    _price->setFntFile("bwnumbers.fnt");
    if (world->getPrice() == 0) {
        _price->setString("Free");
    } else {
        _price->setString(StringUtils::format("%5.02f", world->getPrice()));
    }
    
    _background = SEEK_WIDGET(ImageView*, content, "world_icon");
    _text = SEEK_WIDGET(Text*, content, "world_name");
    setSize(content->getSize());
    setWorld(world);
    
    setTouchEnabled(true);
    
    return true;
}

void WorldButton::playTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type==Widget::TouchEventType::ENDED) {
        if (pSender == _playbutton  &&  onPlayClicked) {
            onPlayClicked(this);
        }
    }
}

bool WorldButton::getActive() {
    return _active;
}

void WorldButton::setActive(bool var) {
    _active = var;
    if (_active) {
        if (_playbutton->getParent() != this) addChild(_playbutton);
    } else {
        removeChild(_playbutton);
    }
}

WorldButton* WorldButton::create(World* world, Widget* content) {
    WorldButton *btn = new WorldButton();
    if (btn->init(world, content)) {
//        btn->setWorld(world);
        return btn;
    }
    return NULL;
}

World* WorldButton::getWorld() {
    return _world;
}

void WorldButton::setWorld(World* val) {
    _world = val;
    CCLOG("Icon: %s", _world->getIcon().c_str());
    //setZOrder(6);
    _background->loadTexture(_world->getIcon());
//    _frame->loadTexture("worlds/world-frame.png");
    
    _text->setString(_world->getName());
    
    auto sz = _content->getSize();
    CCLOG("WorldButton Size: %d, %d", (int)sz.width, (int)sz.height);
}

Scene* WorldSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WorldSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WorldSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();
    
    _worldlist = _PLAYER_->getUniverse();
    
    ADD_JSON_WIDGET("studio/world_select.ExportJson");
    _background = SEEK_WIDGET(ImageView*, widget, "building");
    _background->loadTexture("building-backdrop.png");
    
    _road = SEEK_WIDGET(ImageView*, widget, "road");
    _road->loadTexture("street.png");
    
    auto pavement = SEEK_WIDGET(ImageView*, widget, "pavement");
    pavement->loadTexture("pavement.png");
    
    worlditem_template = SEEK_WIDGET(Widget*, widget, "world_item");
    worlditem_template->setVisible(false);
    worlditem_template->retain();
//    worlditem_template->setVisible(false);
    //widget->removeChild(worlditem_template);
    
    world_listview = SEEK_WIDGET(ListView*, widget, "world_list");
    world_listview->setDirection(ListView::Direction::HORIZONTAL);
    world_listview->setZOrder(5);
    world_listview->removeAllItems();
    world_listview->setItemsMargin(20);
    world_listview->setSize(Size(visibleSize.width, 300));
    world_listview->addEventListener(CC_CALLBACK_2(WorldSelectScene::listviewEvent, this));
    //    ((Widget*)world_listview)->removeChild(worlditem_template);
//    int x = 10, y = visibleSize.height - 300;
    
    // Only list world player can afford
    for (auto world: _worldlist) {
        if (world->getPrice() <= _PLAYER_->getMoney()->getCount() ) {
            WorldButton *worldbutton = WorldButton::create(world, worlditem_template->clone());
            if (worldbutton) {
                worldbutton->onPlayClicked = CC_CALLBACK_1(WorldSelectScene::WorldPlayClicked, this);
                world_listview->pushBackCustomItem(worldbutton);
            }
        }
    }
    
    
    return true;
}

void WorldSelectScene::listviewEvent(Ref* pSender, ListView::EventType type) {
    auto selected = world_listview->getItem(world_listview->getCurSelectedIndex());
    if (!selected) {
        return;
    }
    
    switch (type) {
        case ListView::EventType::ON_SELECTED_ITEM_END:
            for (auto btn: world_listview->getItems()) {
                WorldButton *worldbutton = dynamic_cast<WorldButton*>(btn);
                worldbutton->setActive(selected == btn);
            }
            break;
        case ListView::EventType::ON_SELECTED_ITEM_START:
            
            break;
            
        default:
            break;
    }
}

void WorldSelectScene::WorldPlayClicked(WorldButton* button) {
//    _PLAYER_->setActiveWorld(button->getWorld());
//    Lemonade::printTasteResult(button->getWorld());
    _PLAYER_->enterWorld(button->getWorld());
    Scene* gameScene = TransitionFade::create(2, BusinessLayer::createScene(), Color3B(0,0,0));
    Director::getInstance()->replaceScene(gameScene);
}

void WorldSelectScene::buttonTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type==Widget::TouchEventType::BEGAN) {
        
    } else if (type==Widget::TouchEventType::ENDED) {
        WorldButton *worldButton = dynamic_cast<WorldButton*>(pSender);
        WorldPlayClicked(worldButton);
        
    }
}