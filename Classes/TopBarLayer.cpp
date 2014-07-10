//
//  TopBarLayer.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#include "TopBarLayer.h"
#include "GameVars.h"

bool TopBarLayer::init() {
    
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _topBar = TopBar::create();

    _topBar->setPosition(Point(0, visibleSize.height-100));
    _topBar->setSize(Size(visibleSize.width, 100));
    _topBar->setTouchEnabled(false);
    
//    this->setSize(Size(visibleSize.width, 100));
//    setTouchEnabled(false);
    this->addChild(_topBar);
    
    return true;
}