//
//  TrafficLayer.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-10.
//
//

#include "TrafficLayer.h"

TrafficLayer::TrafficLayer(){
    
}
TrafficLayer::~TrafficLayer() {
    for (auto c: cars) {
        removeChild(c);
    }
    cars.clear();

}

bool TrafficLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    _density = 0.5;
    initView();
    
    return true;
}

void TrafficLayer::restart() {
    for (auto c: cars) {
        removeChild(c);
    }
    cars.clear();
    schedule(schedule_selector(TrafficLayer::UpdateCars), 2, kRepeatForever, 0);
}
void TrafficLayer::initView() {
    restart();
}

void TrafficLayer::UpdateCars(float delta) {
    for (auto c: cars) {
        if (!c->isVisible()) {
            removeChild(c);
        }
    }
    int r = CCRANDOM_0_1() * _density * 180;
    if ( r >= 50) {
        auto car = Car::createRandom(Car::Direction::LEFT);
        cars.pushBack(car);
        addChild(car);
    }
    
    r = CCRANDOM_0_1() * _density * 180;
    if ( r >= 50) {
        auto car = Car::createRandom(Car::Direction::RIGHT);
        cars.pushBack(car);
        addChild(car);
    }
}