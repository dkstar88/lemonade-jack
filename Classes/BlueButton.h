//
//  BlueButton.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-18.
//
//

#ifndef __lemoname__BlueButton__
#define __lemoname__BlueButton__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"

USING_NS_CC;
using namespace cocos2d::ui;

class BlueButton : public Button {
public:
    
    virtual bool init() override;
    
    CREATE_FUNC(BlueButton);
    static BlueButton* createWithTitle(std::string title, float left, float top, float width, float height,
                                       Widget::ccWidgetTouchCallback callback);
    static BlueButton* createWithTitle(std::string title, float width, float height,
                                       Widget::ccWidgetTouchCallback callback);
    static BlueButton* createWithTitle(std::string title, int font_size, float width, float height,
                                       Widget::ccWidgetTouchCallback callback);
    
//    CREATE_FUNC(BlueButton);
};

#endif /* defined(__lemoname__BlueButton__) */
