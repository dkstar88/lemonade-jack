//
//  BuildingsLayer.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-10.
//
//

#include "BuildingsLayer.h"
#include "cocostudio/CocoStudio.h"
#include "stdutil.h"
#include "ValueMapMacros.h"

bool BuildingsLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    
    ADD_JSON_WIDGET("studio/buildings.ExportJson");
    
    auto _background = SEEK_WIDGET(ImageView*, widget, "building");
    _background->loadTexture("building-backdrop.png");
    _background->setPosition(Point(0, 130));
    auto _road = SEEK_WIDGET(ImageView*, widget, "road");
    _road->loadTexture("street.png");
    _road->setPosition(Point(0, 0));
    
    auto _pavement = SEEK_WIDGET(ImageView*, widget, "pavement");
    _pavement->loadTexture("pavement.png");
    _pavement->setPosition(Point(0, 100));

    return true;
    
}