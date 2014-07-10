//
//  LineChart.cpp
//  testproj
//
//  Created by Yang William Yanzhe on 14-6-19.
//
//

#include "LineChart.h"

const int MARGIN = 20;

bool LineChart::init() {
    if (!Layout::init()) {
        return false;
    }
    drawNode = DrawNode::create();
    addChild(drawNode);
    setBackGroundColorType(Layout::BackGroundColorType::GRADIENT);
    setBackGroundColor(Color3B(0, 0, 0), Color3B(0x66, 0x66, 0x66));
    
    _x_axis = new Axis();
    _y_axis = new Axis();
    _lineInfos = new LineInfos();
    return true;
}


inline int round_to(int num, int base) {
    return ((num / base) + 1) * base;
}

inline int delta(int num, int steps) {
    int d = num / steps;
    int c = 0;
    while(d>0)
    {
        d = d / 10;
        c++;
    }
    return (c + 1) * 10;
}

int LineChart::addLine(std::string caption, Color4F color) {
    auto lineinfo = new LineInfo();
    lineinfo->caption = caption;
    lineinfo->color = color;
    _lineInfos->push_back(*lineinfo);
    return _lineInfos->size()-1;
}

void LineChart::addLineData(int lineIndex, float value) {
    LineInfo& lineinfo = _lineInfos->at(lineIndex);
    lineinfo.data.push_back(value);
}

void LineChart::clear() {
    drawNode->clear();
    for (auto label: x_labels) {
        removeChild(label);
    }
    x_labels.clear();
    
    for (auto label: y_labels) {
        removeChild(label);
    }
    y_labels.clear();
    
    _lineInfos->clear();
    getXAxis()->labels.clear();

}

void LineChart::render() {

    Size sz = getContentSize();
    Rect contentRect = Rect(MARGIN+100, MARGIN, sz.width-(MARGIN*2)-100, sz.height - (MARGIN*2));
    drawNode->setPosition(Point(0, 0));
    drawNode->setContentSize(getContentSize());

    float max = 0;
    for (auto lineinfo: *_lineInfos) {
       
        // Work out max first
        for (auto value: lineinfo.data) {
            if (value > max) max = value;
        }
    }
    
    
    
    // Round max to 100s
    max = round_to(max, 100);
    
    float xstep = (contentRect.size.width / _x_axis->labels.size());
    
    for (auto lineinfo: *_lineInfos) {
        float x = contentRect.origin.x;
        std::vector<Point> dataPoints;
        // Work out data points from max value
        for (auto value: lineinfo.data) {
            Point datap = Point(x + (xstep/2), contentRect.origin.y + (value/max * contentRect.size.height));
            dataPoints.push_back(datap);
            x += xstep;
            drawNode->drawDot(datap, 5, lineinfo.color);
        }
        
        
        for (auto iter = dataPoints.begin(); iter+1 != dataPoints.end(); iter++) {
            
            Point p1 = *iter;
            Point p2 = *(iter+1);
            Point mid = Point((p1.x + p2.x)/2, (p1.y + p2.y)/2);
            drawNode->drawSegment(p1, p2, M_PI_2, lineinfo.color);
        }
        
    }
    
    float x = contentRect.origin.x;
    for (auto label: _x_axis->labels) {
        Text* xlabel = Text::create(label, "Arial", 20);
        xlabel->setPosition(Point(x + (xstep/2), contentRect.origin.y  - 10));
        xlabel->setColor(Color3B(0x33, 0x33, 0x33));
        addChild(xlabel);
        x += xstep;
        x_labels.push_back(xlabel);
    }
    
    int ysteps = 10;
    float ystep = (contentRect.size.height / ysteps);
    int y_value_delta = delta(max, ysteps);
    float y = contentRect.origin.y;
    for (int i = 0; i < ysteps; i++) {
        Text* ylabel = Text::create(StringUtils::format("%d", y_value_delta*i), "Arial", 20);
        ylabel->setColor(Color3B(0x33, 0x33, 0x33));
        ylabel->setPosition(Point(contentRect.origin.x - 10, y));
        addChild(ylabel);
        y_labels.push_back(ylabel);
        y += ystep;
    }
    
    
}