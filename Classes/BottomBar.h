//
//  BottomBar.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-26.
//
//

#ifndef __lemoname__BottomBar__
#define __lemoname__BottomBar__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "ItemListItem.h"
#include "Player.h"

USING_NS_CC;
using namespace cocos2d::ui;

class BottomBar : public Layout {
    
public:
    virtual bool init() override;
    
    CC_SYNTHESIZE(LayerMultiplex*, _tabbedLayer, TabbedLayer);
    std::function<bool(Ref*, int)> onButtonClicked;
    CREATE_FUNC(BottomBar);
    void iconTouchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void registerIcon(std::string widgetName);
//    virtual bool onTouchBegan(Touch* touch, Event* event);
//    virtual void onTouchEnded(Touch* touch, Event* event);
//    virtual void onTouchCancelled(Touch* touch, Event* event);
//    virtual void onTouchMoved(Touch* touch, Event* event);
    
//    Widget* getItemForPoint(Node* parent, Point location);
    
protected:
    void menuCallback(Ref* pSender);
    Vector<ImageView*> iconlist;
    
private:
//    int currentTab;
    
};

#endif /* defined(__lemoname__BottomBar__) */
