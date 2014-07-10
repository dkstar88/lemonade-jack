//
//  TrafficLayer.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-10.
//
//

#ifndef __teaegg__TrafficLayer__
#define __teaegg__TrafficLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Car.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class TrafficLayer : public cocos2d::Layer
{
public:
    
    CC_SYNTHESIZE(float, _density, Density);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void initView();
    void UpdateCars(float delta);
    void restart();
    
    TrafficLayer();
    ~TrafficLayer();
    // implement the "static create()" method manually
    CREATE_FUNC(TrafficLayer);
    
    
private:
    
    Vector<Car*> cars;

    
    
};

#endif /* defined(__teaegg__TrafficLayer__) */
