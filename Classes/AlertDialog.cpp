//
//  AlertDialog.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-4.
//
//

#include "AlertDialog.h"
#include "ValueMapMacros.h"

void AlertDialog::Alert(std::string _title, std::string _message, std::string _icon, ONCLOSE_EVENT _onClose ) {
    AlertDialog* alertdialog = AlertDialog::create();
    if (alertdialog) {
        alertdialog->setAttribs(_title, _message, _icon);
        alertdialog->onClose = _onClose;
        alertdialog->setOpacity(100);
//        Size visibleSize = Director::getInstance()->getVisibleSize();
        alertdialog->setAnchorPoint(Point(0, 0));
        alertdialog->setPosition(Point(0, 0));
        alertdialog->addButton("OK");
        Director::getInstance()->getRunningScene()->addChild(alertdialog, 99);
        alertdialog->runAction( Sequence::create( FadeIn::create(0.5), CallFunc::create( [](void) {
            // TODO: Add onShow Event
        }), NULL));
    }
}

void AlertDialog::Confirm(std::string _title, std::string _message, std::string _icon, ONBUTTONPRESSED_EVENT _onClose ) {
    AlertDialog* alertdialog = AlertDialog::create();
    if (alertdialog) {
        alertdialog->setAttribs(_title, _message, _icon);
        alertdialog->onButtonPressed = _onClose;
        alertdialog->setOpacity(0);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        alertdialog->setAnchorPoint(Point(0, 0));
        alertdialog->addButton("Yes");
        alertdialog->addButton("No");
        alertdialog->setPosition(Point(0, 0));
        Director::getInstance()->getRunningScene()->addChild(alertdialog, 99);
        alertdialog->runAction( Sequence::create( FadeIn::create(0.5), CallFunc::create( [](void) {
            // TODO: Add onShow Event
        }), NULL));
    }
}

void AlertDialog::setAttribs(std::string _title, std::string _message, std::string _icon) {
    if (title) {
        title->setString(_title);
    }
    
    if (message) {
        message->setString(_message);
    }
    
    if (icon && _icon.length() && FileUtils::getInstance()->isFileExist(_icon)) {
        icon->loadTexture(_icon);
    }
}

bool AlertDialog::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 80))) {
        return false;
    }
    

    ADD_JSON_WIDGET("studio/dialog.ExportJson");

    icon = SEEK_WIDGET(ImageView*, widget, "dialog_icon");
    title = SEEK_WIDGET(Text*, widget, "dialog_title");
    message = SEEK_WIDGET(Text*, widget, "text");
    message->setTextHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    ASSOC_BUTTON(closebtn, widget, "close_button", AlertDialog::touchEvent)
    closebtn->retain();
    auto container = SEEK_WIDGET(Layout*, widget, "button_container");
    container->removeAllChildren();
    
    return true;
}

void AlertDialog::addButton(std::string button_caption) {
    auto container = SEEK_WIDGET(Layout*, (Widget*)this, "button_container");
    auto button = (Button*)closebtn->clone();
    button->setTitleText(button_caption);
    button->setTitleColor(Color3B(0, 0, 0));
    container->addChild(button);
}

void AlertDialog::doClose(Ref* pSender) {
    this->runAction( Sequence::create( FadeOut::create(0.5), CallFunc::create( [this, pSender](void) {
        this->removeFromParentAndCleanup(true);
        if (this->onButtonPressed) {
            onButtonPressed(pSender, ((Button*)pSender)->getTitleText());
        }
        if (this->onClose) {
            this->onClose(pSender);
        }
    }), NULL));

}

void AlertDialog::touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type==Widget::TouchEventType::ENDED) {
        doClose(pSender);
    }
}