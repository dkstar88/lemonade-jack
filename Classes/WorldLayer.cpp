//
//  WorldLayer.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#include "WorldLayer.h"

bool WorldLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    image = ImageView::create();
    image->setSize(Size(300, 240));
    image->setAnchorPoint(Point(0, 0));
    image->setPosition(Point(20, visibleSize.height-250));
    addChild(image);
    
    title = Text::create();
    title->setFontSize(36.0);
    title->setTextHorizontalAlignment(TextHAlignment::LEFT);
    title->setPosition(Point(420, visibleSize.height-120));
    addChild(title);
    
    desc = Text::create();
    desc->setFontSize(24);
    desc->setAnchorPoint(Point(0, 0));
    desc->setSize(Size(visibleSize.width-20, 25));
    desc->setPosition(Point(0 , 0));
    auto scroller = ScrollView::create();
    scroller->setSize(Size(visibleSize.width-20, 250));
    scroller->setAnchorPoint(Point(0, 0));
    scroller->addChild(desc);
    scroller->setBackGroundImage("dark-well.png");
    scroller->setBackGroundImageCapInsets(Rect(22, 22, 60, 60));
    scroller->setBackGroundImageScale9Enabled(true);
    scroller->setPosition(Point(10, 120));
    addChild(scroller);
    
    return true;
}

void WorldLayer::setWorld(Lemonade::World* val) {
    _world = val;
    if (_world) {
        image->loadTexture(_world->getIcon());
        title->setString(_world->getName());
        desc->setString(_world->getDesc());
//        _back->loadTexture(_world->getIcon());
//        _back->setScale(5);
    }
}

Lemonade::World* WorldLayer::getWorld() {
    return _world;
}
