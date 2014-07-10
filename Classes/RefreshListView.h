//
//  RefreshListView.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-21.
//
//

#ifndef __lemoname__RefreshListView__
#define __lemoname__RefreshListView__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Refreshable.h"

USING_NS_CC;
using namespace cocos2d::ui;

class RefreshListView : public ListView, public Refreshable {
public:
    virtual bool init() override;

    void UpdateUI(float delta);
    
    virtual void refresh() override;

    
    //    CREATE_CLASS_WIDGET_READER_INFO(ItemListView);
    CREATE_FUNC(RefreshListView);
    
};

#endif /* defined(__lemoname__RefreshListView__) */
