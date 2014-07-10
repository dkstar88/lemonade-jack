//
//  RefreshListView.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-21.
//
//

#include "RefreshListView.h"


bool RefreshListView::init() {
    if (ListView::init()){
        this->schedule(schedule_selector(RefreshListView::UpdateUI), 1, kRepeatForever, 0);
        return true;
    } else {
        return false;
    }
}

void RefreshListView::UpdateUI(float delta) {
    refresh();
}

void RefreshListView::refresh() {
    for (Node* item: this->getChildren()) {
        Refreshable* ref = dynamic_cast<Refreshable*>(item);
        ref->refresh();
    }
}