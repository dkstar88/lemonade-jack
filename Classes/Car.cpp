//
//  Car.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-6.
//
//

#include "Car.h"
#include "ValueMapMacros.h"
#include "stdutil.h"
#include "cocostudio/cocostudio.h"
#include "SoundUtil.h"
#include "Game.h"

#define WHEEL_ROTATE_TIME (1.0f)
#define DRIVE_TIME (5.0f)

const char* CAR_MODELS[] = { "red_hatchback", "silver_hatchback", "purple_convertible",
      "red_smart", "silver_beatle", "green_hatchback"
};

static std::map<std::string, Widget*> _CAR_MODEL_CACHE;

Widget* Car::getCarModel(std::string modelName) {
    if (_CAR_MODEL_CACHE.find(modelName) == _CAR_MODEL_CACHE.end()) {
        auto jsonFile = StringUtils::format("studio/%s.ExportJson", modelName.c_str());
        Widget *widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(jsonFile.c_str());
        widget->retain();
        _CAR_MODEL_CACHE[modelName]=widget;
    }
    return _CAR_MODEL_CACHE[modelName];
}

bool Car::init() {
    std::string carmodel = "red_hatchback";
    return initWithName(carmodel, Direction::LEFT);

}

std::string Car::getRandomModel() {
    int r = sizeof(CAR_MODELS) / sizeof(char*);
	r = rand() % r;
    return CAR_MODELS[r];
}

bool Car::initWithName(std::string &modelName, Car::Direction dir) {
    if (!Layout::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _car_model = modelName;
    Widget *widget = Car::getCarModel(_car_model)->clone();
    addChild(widget);
    
    _car_body = SEEK_WIDGET(ImageView*, widget, "body");
    _left_wheel = SEEK_WIDGET(ImageView*, widget, "left_wheel");
    _right_wheel = SEEK_WIDGET(ImageView*, widget, "right_wheel");

    
    int rotateAngle;
    Point startPos, endPos;
    
    if (dir == Direction::LEFT) {
        
        rotateAngle = -360;
        startPos = Point(visibleSize.width, 10);
        endPos = Point(-300, 10);
        this->setLocalZOrder(50);
        
    } else {
        
        rotateAngle = 360;
        startPos = Point(-100, 75);
        endPos = Point(visibleSize.width, 75);
        widget->setScale(0.9);
        widget->setFlippedX(true);
        _car_body->setFlippedX(true);
        _left_wheel->setFlippedX(true);
        _right_wheel->setFlippedX(true);
        this->setLocalZOrder(40);
        
    }
//    // Play car horn
//    if (CCRANDOM_0_1()*100 > 80) {
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/horn.mp3");
//    }
    widget->addTouchEventListener(CC_CALLBACK_2(Car::TouchEvent, this));
    
    auto rotate = RepeatForever::create(RotateBy::create(WHEEL_ROTATE_TIME/_GAME_SPEED_, rotateAngle));
    _left_wheel->runAction(rotate);
    _right_wheel->runAction(rotate->clone());
    widget->setPosition(startPos);
    auto seq = Sequence::create(MoveTo::create(DRIVE_TIME/_GAME_SPEED_, endPos), CallFunc::create(CC_CALLBACK_0(Car::animFinish, this)), NULL);
    widget->runAction( seq );
    return true;
    
}

void Car::animFinish() {
    this->setVisible(false);
}

void Car::TouchEvent(cocos2d::Ref *pSender, TouchEventType type) {
    if (type == TouchEventType::BEGAN) {
        SoundUtil::playRndSoundAt(this, "car");
    }
}