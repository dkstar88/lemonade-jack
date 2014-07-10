//
//  BottomBar.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-26.
//
//

#include "BottomBar.h"
#include "cocostudio/CocoStudio.h"
#include "stdutil.h"
#include "GameVars.h"

bool BottomBar::init() {
    if (!Layout::init()) {
        return false;
    }
    Widget *widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("studio/bottom_bar.ExportJson");
    addChild(widget);
    setSize(Director::getInstance()->getVisibleSize());
    auto layout = RelativeLayoutParameter::create();
    layout->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
    widget->setLayoutParameter(layout);
    registerIcon("shop");
    registerIcon("people");
    registerIcon("open");
    registerIcon("recipe");
    registerIcon("awards");
    registerIcon("chart");
    registerIcon("sound");
    
    Layout* button_template = SEEK_WIDGET(Layout*, widget, "button");
    if (button_template) button_template->setVisible(false);
    this->setPassFocusToChild(true);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    setSize(Size(visibleSize.width, 135));
    
//    setBackGroundColor(Color3B(0xFF, 0xFF, 0xFF));
//    setBackGroundColorType(BackGroundColorType::SOLID);
    return true;
}

void BottomBar::registerIcon(std::string widgetName) {
    
    Button* icon = dynamic_cast<Button*>(Helper::seekWidgetByName(this, widgetName.c_str()));
    icon->addTouchEventListener(CC_CALLBACK_2(BottomBar::iconTouchEvent,this));
    
    
}

void BottomBar::iconTouchEvent(cocos2d::Ref *pSender, TouchEventType type) {
    Node* target = dynamic_cast<Node*>(pSender);
    if (type==TouchEventType::ENDED) {
        int idx = target->getTag();
        bool canSwitch = true;
        if (onButtonClicked) {
            canSwitch = onButtonClicked(this, idx);
        }
        if (canSwitch && _tabbedLayer) {
            _tabbedLayer->switchTo(idx);
        }

    } else if (type==TouchEventType::BEGAN) {
        for (auto icon: iconlist) {
            if (icon == target) {
                icon->runAction(ScaleTo::create(0.5, 1.2));
            } else {
                icon->runAction(ScaleTo::create(0.5, 1));
            }
        }
    }
//    refresh();
}
