//
//  SalesChart.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#ifndef __teaegg__SalesChart__
#define __teaegg__SalesChart__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "ItemListView.h"
#include "TopBar.h"
#include "LineChart.h"

USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class SalesChartLayer : public cocos2d::Layer, public Refreshable
{
public:
    virtual bool init() override;
//    void UpdateUI(float delta);
    void refresh();
    CREATE_FUNC(SalesChartLayer);
    //    ShopListItem* find(Lemonade::Item* item);
private:
    LineChart* lineChart;
//    ListView* listview;
//    Layout* item_template;
};


#endif /* defined(__teaegg__SalesChart__) */
