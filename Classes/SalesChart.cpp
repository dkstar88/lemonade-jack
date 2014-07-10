//
//  SalesChart.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#include "SalesChart.h"
#include "GameVars.h"
#include "DayRecord.h"

bool SalesChartLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    ADD_JSON_WIDGET("studio/sales_chart.ExportJson");
    auto container = SEEK_WIDGET(Layout*, widget, "content");
    
    lineChart = LineChart::create();
    auto param = RelativeLayoutParameter::create();
    param->setAlign(RelativeAlign::LOCATION_BELOW_LEFTALIGN);
    param->setMargin(Margin(0, 0, 0, 100));
    lineChart->setLayoutParameter(param);
    container->addChild(lineChart);
//    lineChart->setAnchorPoint(Point(0.5, 0.5));
//    lineChart->setPosition(container->getPosition());
    lineChart->setContentSize(Size(visibleSize.width*0.9f, visibleSize.height-400));
    container->setPosition(Point(0, 100));
    container->setSize(Size(visibleSize.width*0.9f, visibleSize.height-160));
    return true;
}

void SalesChartLayer::refresh() {
    auto container = SEEK_WIDGET(Layout*, (Widget*)this, "content");
    lineChart->clear();
    Size sz = container->getSize();
    sz.height -= 50;
    lineChart->setContentSize(sz);
    int startDay = fmax(1, _PLAYER_->getDay()-30);
    lineChart->addLine("Money Earned", Color4F(0, 1, 0, 1));
    lineChart->addLine("Money Spent", Color4F(1, 0, 0, 1));

    for (int i = startDay; i <=_PLAYER_->getDay(); i++) {
        DayRecord *dayRecord = DayRecords::getDayRecord(i);
        lineChart->addLineData(0, dayRecord->getEarned());
        lineChart->addLineData(1, dayRecord->getSpent());
        lineChart->getXAxis()->labels.push_back(StringUtils::format("Day %d", i));
    }
    
    lineChart->render();
}