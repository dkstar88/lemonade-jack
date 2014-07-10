//
//  WorldSelectScene.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#ifndef __lemoname__WorldSelectScene__
#define __lemoname__WorldSelectScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "World.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class WorldButton: public Layout {
public:
    virtual bool init(World* world, Widget* content);
    CC_PROPERTY(World*, _world, World);
    CC_PROPERTY(bool, _active, Active);
//    CREATE_FUNC(WorldButton);
    std::function<void(WorldButton*)> onPlayClicked;
    void playTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    static WorldButton* create(World* world, Widget* content);
    
private:
    ImageView *_background, *_frame;
    Button *_playbutton;
    TextBMFont *_price;
    Text *_rating;
    Widget* _content;
    ImageView *_icon;
    Text* _text;
};

class WorldSelectScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
//    void initView();
    
//    void touchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void buttonTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void listviewEvent(Ref* pSender, ListView::EventType type);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WorldSelectScene);
    
    
private:
    void WorldPlayClicked(WorldButton* button);
    
    ListView* world_listview;
    ImageView *_background, *_road;

    Widget* worlditem_template;
    Vector<WorldButton*> _buttons;
    std::vector<Lemonade::World*> _worldlist;
    ListView* _listview;
    
};


#endif /* defined(__lemoname__WorldSelectScene__) */
