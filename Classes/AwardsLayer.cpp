//
//  AwardsLayer.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#include "AwardsLayer.h"

bool AwardsLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    
    ADD_JSON_WIDGET("studio/awards.ExportJson");
    
    listview = SEEK_WIDGET(ListView*, widget, "awardlist");
    return true;
}


void AwardsLayer::UpdateUI(float delta) {
    
}

void AwardsLayer::refresh() {
    
}