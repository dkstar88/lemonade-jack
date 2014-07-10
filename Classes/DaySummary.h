//
//  DaySummary.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-22.
//
//

#ifndef __lemoname__DaySummary__
#define __lemoname__DaySummary__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "RefreshListView.h"
#include "DayRecord.h"
//#include "TopBar.h"

USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class DaySummaryLayer : public cocos2d::LayerColor {
public:
    virtual bool init() override;
    void refresh();
    virtual void close(Ref* pSender);
    CC_SYNTHESIZE(Lemonade::DayRecord*, _dayRecord, DayRecord);
//    CC_SYNTHESIZE(long, _income, Income);
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    virtual bool onTouchBegan(Touch *touch, Event *event);
//    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
//    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
//    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
    std::function<bool(Ref*)> onClose;
    
    CREATE_FUNC(DaySummaryLayer);
    static DaySummaryLayer* create(Lemonade::DayRecord* _dayRecord);
    
protected:
    
    ListView *listview;
    Widget* itemtemp;
    Button* closebtn;
    //    ImageView* image;
    //    Text *title, *desc;
    
    
};

#endif /* defined(__lemoname__DaySummary__) */
