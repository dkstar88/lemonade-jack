//
//  BuildingsLayer.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-10.
//
//

#ifndef __teaegg__BuildingsLayer__
#define __teaegg__BuildingsLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Car.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class BuildingsLayer : public cocos2d::Layer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

    
    // implement the "static create()" method manually
    CREATE_FUNC(BuildingsLayer);
    
    
private:
    
//    Vector<Car*> cars;
    
    
    
};

#endif /* defined(__teaegg__BuildingsLayer__) */
