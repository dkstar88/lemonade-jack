//
//  MenuScene.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#ifndef __lemoname__MenuScene__
#define __lemoname__MenuScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

using namespace cocos2d::ui;

class MenuScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // Menu Actions
    void newGame();
    void playGame();
    void options();
    void help();
    void about();
    
    // a selector callback
    void buttonTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
//    void newGameCallback(cocos2d::Ref* pSender);
//    void continueGameCallback(cocos2d::Ref* pSender);
//    void optionsCallback(cocos2d::Ref* pSender);
//    void helpCallback(cocos2d::Ref* pSender);
//    void aboutCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
    
private:
    void loadView();
    Button *btnPlay, *btnNewGame, *btnOptions, *btnHelp, *btnAbout;
    
};

#endif /* defined(__lemoname__MenuScene__) */
