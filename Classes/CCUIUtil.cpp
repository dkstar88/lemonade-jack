//
//  CCUIUtil.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-3.
//
//

#include "CCUIUtil.h"

void GUIUtil::EnumWidgets(Widget* root, std::function<bool(Widget* widget)> callback) {
    if (!root)
    {
        return;
    }
    
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            if (!callback(child)) {
                return;
            }
        }
        Widget* widget = dynamic_cast<Widget*>(subWidget);
        if (widget) {
            EnumWidgets(child, callback);
        }
    }
    return;
}

void GUIUtil::SetFntToAll(Widget* root, const char* FntFile) {
    GUIUtil::EnumWidgets(root, [FntFile](Widget* widget) {
        TextBMFont* bmtext = dynamic_cast<TextBMFont*>(widget);
        if (bmtext) bmtext->setFntFile(FntFile);
        return true;
    });
}