//
//  TestScene.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-9.
//
//

#ifndef __lemoname__TestScene__
#define __lemoname__TestScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "ItemListView.h"
#include "TopBar.h"

USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class TestScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void testData();
    
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene);
    
    
private:
    TopBar *_topBar;
    Player* player;
    World *world;
    ItemListView* listview;
    
};

#endif /* defined(__lemoname__TestScene__) */
