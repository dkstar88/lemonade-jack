//
//  CCUIUtil.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-3.
//
//

#ifndef __Lemonade_Jack__CCUIUtil__
#define __Lemonade_Jack__CCUIUtil__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class GUIUtil {
public:
    static void EnumWidgets(Widget* root, std::function<bool(Widget* widget)> callback);
    static void SetFntToAll(Widget* root, const char* FntFile);
};

#endif /* defined(__Lemonade_Jack__CCUIUtil__) */
