//
//  GameScene.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#ifndef __lemoname__GameScene__
#define __lemoname__GameScene__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "ItemListView.h"
#include "TopBar.h"
#include "TopBarLayer.h"
#include "WorldLayer.h"
#include "ShopLayer.h"
#include "PeopleInfoLayer.h"
#include "BusinessScene.h"
#include "BottomBar.h"
#include "RecipeTweakLayer.h"
#include "AwardsLayer.h"
#include "SalesChart.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class GameScene : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    CC_PROPERTY(Lemonade::World*, _world, World);
    CC_SYNTHESIZE(Lemonade::Player*, _player, Player);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    void initView();
    void gotoBusinessScene();
//    void touchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void switchTab(int tag);
    // a selector callback
    bool tabButtonClicked(Ref* pSender, int index);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCallback(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    
private:
    int curLayerPos = 0;
    LayerMultiplex *tabLayers;
//    WorldLayer* _world_layer;
    ShopLayer* _shop_layer;
    TopBarLayer* _top_bar_layer;
    PeopleInfoLayer* _people_layer;
    BusinessLayer* _business_layer;
    RecipeTweakLayer* _recipe_layer;
    SalesChartLayer* _chart_layer;
    AwardsLayer* _awards_layer;
    BottomBar* bottom_bar;
};


#endif /* defined(__lemoname__GameScene__) */
