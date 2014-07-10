//
//  GameScene.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#include "GameScene.h"
#include "ItemListItem.h"
#include <algorithm>
#include "MenuScene.h"
#include "GameVars.h"
#include "BuildingsLayer.h"
#include "OptionsScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DIAAchievement.h"
#endif
#include "WorldSelectScene.h"


USING_NS_CC;
using namespace cocos2d::ui;

Scene* GameScene::createScene()
{

    
    // 'layer' is an autorelease object
    auto scene = GameScene::create();
    
    // return the scene
    return scene;
}

void GameScene::onEnter() {
    Scene::onEnter();
    CCLOG("Player: %s", _PLAYER_->getInventory()->getDescription().c_str());
    tabButtonClicked(NULL, 0);
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    _player = _PLAYER_;
    _world = _player->getActiveWorld();

    //Init test data
    initView();
    GlobalVars::SaveGame();
    return true;
}

void GameScene::initView() {

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sfx/Go on (You can).mp3", true);
    auto _background = BuildingsLayer::create();
    addChild(_background);

    _top_bar_layer = TopBarLayer::create();
    
    addChild(_top_bar_layer, 20);
    
    _shop_layer = ShopLayer::create();
    _shop_layer->setTag(0);

    _people_layer = PeopleInfoLayer::create();
    _people_layer->setWorld(_world);
    _people_layer->setTag(1);
    
    _recipe_layer = RecipeTweakLayer::create();
    _recipe_layer->setTargetItem(_PRODUCTION_);
    _recipe_layer->setTag(2);
    
    _chart_layer = SalesChartLayer::create();
    _chart_layer->setTag(3);
    
//    _awards_layer = AwardsLayer::create();
//    _awards_layer->setTag(3);
    
    tabLayers = LayerMultiplex::create(_shop_layer, _people_layer, _recipe_layer,  _chart_layer, NULL);
    tabLayers->switchTo(0);
    addChild(tabLayers);
    
    bottom_bar = BottomBar::create();
    bottom_bar->setPosition(Point(0, 0));
    bottom_bar->setTabbedLayer(tabLayers);
    bottom_bar->onButtonClicked = CC_CALLBACK_2(GameScene::tabButtonClicked, this);
    addChild(bottom_bar);
}

bool GameScene::tabButtonClicked(Ref* pSender, int index) {
    if (index!=curLayerPos)
    {
        
        curLayerPos=index;
        if (curLayerPos == 99) {
            auto scene = TransitionFade::create(2, WorldSelectScene::createScene(),
                                                Color3B(0,0,0));

            Director::getInstance()->pushScene(scene);
//            _business_layer->dayStart();
//            bottom_bar->setVisible(false);
//            _top_bar_layer->setVisible(false);
        } else if (curLayerPos == 98) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            sGameCenter->openGameCenter();
#endif
        } else if (curLayerPos == 97) {
            Director::getInstance()->pushScene(OptionsLayer::createScene());
        } else {
            tabLayers->switchTo(index);//切换布景，如果使用switchToAndReleaseMe会释放掉当前布景
//            bottom_bar->setVisible(true);
//            _top_bar_layer->setVisible(true);
        }
        
        auto currLayer = tabLayers->getChildByTag(index);
        if (auto refreshable = dynamic_cast<Refreshable*>(currLayer)) {
            refreshable->refresh();
        }
//        if (curLayerPos == 0) {
//            // Shop Layer
//            _shop_layer->refresh();
//        }
        return false;
    } else {
        return false;
    }
}

void GameScene::gotoBusinessScene() {
//    auto scene = TransitionMoveInB::create(0.5, BusinessScene::createScene(_world));
//    Director::getInstance()->replaceScene(scene);
}

void GameScene::setWorld(Lemonade::World* val) {
    _world = val;
}

void GameScene::switchTab(int tag) {
    if (tag!=curLayerPos)
    {
        tabLayers->switchTo(tag);//切换布景，如果使用switchToAndReleaseMe会释放掉当前布景
        curLayerPos=tag;
        if (curLayerPos == 3) {
            _business_layer->dayStart();
        }
    }
}

void GameScene::menuCallback(Ref* pSender)
{
    int item=((MenuItem*)pSender)->getTag();//获取选择项
    switchTab(item);
}

Lemonade::World* GameScene::getWorld() {
    return _world;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(MenuScene::createScene());
}
