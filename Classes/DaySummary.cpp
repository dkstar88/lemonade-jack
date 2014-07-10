//
//  DaySummary.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-22.
//
//

#include "DaySummary.h"
#include "cocostudio/CocoStudio.h"
#include "ItemListItem.h"

bool DaySummaryLayer::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 80))) {
        return false;
    }
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    
//    setGlobalZOrder(90);
    ADD_JSON_WIDGET("studio/DaySummary.ExportJson");
//    widget->setGlobalZOrder(99);
    listview = SEEK_WIDGET(ListView*, widget, "solditems");
    itemtemp = SEEK_WIDGET(Widget*, widget, "listitem");
    itemtemp->setVisible(false);
    ASSOC_BUTTON(closebtn, widget, "close_button", DaySummaryLayer::touchEvent)
    
    auto el2 = EventListenerTouchOneByOne::create();
    el2->onTouchBegan = CC_CALLBACK_2(DaySummaryLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(el2, closebtn);
    return true;
}

void DaySummaryLayer::close(Ref* pSender) {
    if (onClose) {
        onClose(pSender);
    }
}
void DaySummaryLayer::touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type==Widget::TouchEventType::ENDED) {
        if (pSender == closebtn) {
            // Close Button
            close(pSender);
            this->removeFromParentAndCleanup(true);
        }
    }
}

bool DaySummaryLayer::onTouchBegan(Touch *touch, Event *event) {
    close(this);
    this->removeFromParentAndCleanup(true);
    return true;
}

//void DaySummaryLayer::onTouchesCancelled(const std::vector<Touch *> &touches, cocos2d::Event *unused_event) {
//    
//}
//
//void DaySummaryLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event) {
//    
//}
//
//void DaySummaryLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) {
//    
//}

void DaySummaryLayer::refresh() {
    if (listview && _dayRecord) {
        
        for (auto iter: _dayRecord->getSoldItems()) {
            auto listitem = itemtemp->clone();
        
            auto node = Helper::seekWidgetByName(listitem, "icon");
            
            auto item = Lemonade::Item::create(iter.first);
            
            ImageView* icon = dynamic_cast<ImageView*>(node);
            icon->loadTexture(item->getIcon());
            
            Text* text = dynamic_cast<Text*>(Helper::seekWidgetByName(listitem, "text"));
            char buf[80] = {};
            sprintf(buf, "%d Sold", (int)ceil(iter.second));
            text->setString(buf);
            
            Text* income = dynamic_cast<Text*>(Helper::seekWidgetByName(listitem, "income"));

            sprintf(buf, "%5.2f", iter.second * item->getPrice());
            income->setString(buf);
            listitem->setVisible(true);
            listview->pushBackCustomItem(listitem);
        }

    }
}

DaySummaryLayer* DaySummaryLayer::create(Lemonade::DayRecord* dayRecord) {
    DaySummaryLayer* layer = new DaySummaryLayer();
    if (layer->init()) {
        layer->setDayRecord(dayRecord);
        layer->refresh();
        return layer;
    }
    return NULL;

}