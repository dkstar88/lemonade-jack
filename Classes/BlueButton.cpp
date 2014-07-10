//
//  BlueButton.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-18.
//
//

#include "BlueButton.h"

bool BlueButton::init() {
    if (Button::init()) {
        this->loadTextures("blue-button.png", "orange-button.png");
        this->setScale9Enabled(true);
        this->setCapInsets(Rect(20, 20, 138, 138));
        this->setTitleFontSize(26.0);
        this->setTitleFontName("Helvetica-Bold");
        return true;
    }
    return false;
}

BlueButton* BlueButton::createWithTitle(std::string title, int font_size, float width, float height,
                                        Widget::ccWidgetTouchCallback callback) {
    BlueButton *btn = BlueButton::create();
    if (btn) {
        btn->setTitleFontName("Helvetica-Bold");
        btn->setTitleText(title);
        btn->setTitleFontSize(font_size);
        btn->setSize(Size(width, height));
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(callback);
        return btn;
    } else {
        return NULL;
    }
}

BlueButton* BlueButton::createWithTitle(std::string title, float left, float top, float width, float height, Widget::ccWidgetTouchCallback callback){
    BlueButton *btn = BlueButton::create();
    if (btn) {
        btn->setTitleFontName("Helvetica-Bold");
        btn->setTitleText(title);
        btn->setPosition(Point(left, top));
        btn->setSize(Size(width, height));
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(callback);
        return btn;
    } else {
        return NULL;
    }
}

BlueButton* BlueButton::createWithTitle(std::string title, float width, float height,
                                        Widget::ccWidgetTouchCallback callback) {
    BlueButton *btn = BlueButton::create();
    if (btn) {
        btn->setTitleText(title);
        btn->setSize(Size(width, height));
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(callback);
        return btn;
    } else {
        return NULL;
    }
}