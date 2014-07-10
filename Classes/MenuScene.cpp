//
//  MenuScene.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-19.
//
//

#include "MenuScene.h"
#include "WorldSelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ValueMapMacros.h"
#include "TrafficLayer.h"
#include "BuildingsLayer.h"
#include "GameVars.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DIAAchievement.h"
#endif
#include "GameScene.h"
#include "OptionsScene.h"
#include "AlertDialog.h"

Scene* MenuScene::createScene() {
    
//    Director::getInstance()->setAnimationInterval(1/15);
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MenuScene::init() {
    if (Layer::init()) {
        loadView();
        return true;
    }
    return false;
}

void MenuScene::loadView() {
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sfx/Time is wasting.mp3", true);

    auto buildings = BuildingsLayer::create();
    addChild(buildings);
    
    ADD_JSON_WIDGET("studio/StartMenu.ExportJson");
    
//    auto logo = SEEK_WIDGET(ImageView*, widget, "logo");
//    logo->loadTexture("logo.png");

    ASSOC_BUTTON(btnAbout, widget, "btnAbout", MenuScene::buttonTouchEvent);
    ASSOC_BUTTON(btnPlay, widget, "btnPlay", MenuScene::buttonTouchEvent);
    ASSOC_BUTTON(btnNewGame, widget, "btnNewGame", MenuScene::buttonTouchEvent);
    ASSOC_BUTTON(btnOptions, widget, "btnOptions", MenuScene::buttonTouchEvent);
    ASSOC_BUTTON(btnHelp, widget, "btnHelp", MenuScene::buttonTouchEvent);
    
    auto traffics = TrafficLayer::create();
    addChild(traffics);
    
    
}
// a selector callback
void MenuScene::buttonTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		if (pSender == btnNewGame) {
			newGame();
		} else if (pSender == btnPlay) {
			playGame();
		} else if (pSender == btnOptions) {
			options();
		} else if (pSender == btnHelp) {
			help();
		} else if (pSender == btnAbout) {
			about();
		}
	}
}

void MenuScene::newGame() {
    AlertDialog::Confirm("New Game", "Start a new game will erase your current game progress,\
 including earned gold coins, reputation, stock.\
 However you will not lose your purchased diamonds or game features such as game speed hacking.", "",
                         
                         [](Ref* pSender, std::string button)->bool {
                             
                             if (button == "Yes") {
                                 GlobalVars::NewGame();
                                 auto scene = TransitionFade::create(1, GameScene::createScene(), Color3B(0,0,0));
                                 Director::getInstance()->pushScene(scene);
                             }
                             return true;
                         }
                         
                         );

}
void MenuScene::playGame() {
    GlobalVars::LoadGame();
//    glColor4f(0, 0, 0, 1);
    auto scene = TransitionFade::create(1, GameScene::createScene(), Color3B(0,0,0));

    Director::getInstance()->pushScene(scene);
}

void MenuScene::options() {
    
    
    Director::getInstance()->pushScene(OptionsLayer::createScene());

}
void MenuScene::help() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sGameCenter->showLeaderboard();
#endif
}
void MenuScene::about() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    sGameCenter->showLeaderboard();
    sGameCenter->openGameCenter();
#endif
//    auto gamecenter = new avalon::GameCenter();
//    gamecenter->login();
}
