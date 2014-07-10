//
//  Car.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-6.
//
//

#ifndef __teaegg__Car__
#define __teaegg__Car__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "BlueButton.h"
#include "Player.h"
#include "Refreshable.h"

USING_NS_CC;
using namespace cocos2d::ui;

class Car : public Layout {

    
    
public:
    
    enum Direction {
        LEFT, RIGHT
    };
    
    virtual bool init() override;
    virtual bool initWithName(std::string &modelName, Car::Direction dir);
    CC_SYNTHESIZE(std::string, _car_model, CarModel);
    CC_SYNTHESIZE(Car::Direction, _dir, Direction);
    
    CREATE_FUNC(Car);
    
    void TouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    
    static std::string getRandomModel();
    
    static Widget* getCarModel(std::string modelName);
    static Car* createRandom(Car::Direction dir) {
        Car* car = new Car();
        std::string modelName = Car::getRandomModel();
        if (car->initWithName(modelName, dir)) {
            return car;
        } else {
            return NULL;
        }
    }
    static Car* createWithModel(std::string &modelName, Car::Direction dir) {
        Car* car = new Car();
        if (car->initWithName(modelName, dir)) {
            return car;
        } else {
            return NULL;
        }
    }

protected:

    ImageView *_car_body, *_left_wheel, *_right_wheel;

    void animFinish();
};

#endif /* defined(__teaegg__Car__) */
