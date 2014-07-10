//
//  LineChart.h
//  testproj
//
//  Created by Yang William Yanzhe on 14-6-19.
//
//

#ifndef __testproj__LineChart__
#define __testproj__LineChart__


#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocos2d::ui;

struct LineInfo {
    std::string caption;
    Color4F color;
    std::vector<float> data;
};

typedef std::vector<LineInfo> LineInfos;

struct Axis {
    std::string caption;
    Color4F color;
    std::vector<std::string> labels;
};

class LineChart: public Layout {
public:
    virtual bool init();
    CC_SYNTHESIZE(Axis*, _x_axis, XAxis);
    CC_SYNTHESIZE(Axis*, _y_axis, YAxis);
    CC_SYNTHESIZE(LineInfos*, _lineInfos, LineInfos);
    
    int addLine(std::string caption, Color4F color);
    void addLineData(int lineIndex, float value);
    void clear();
    void render();
    
    CREATE_FUNC(LineChart);
private:
    std::vector<Text*> x_labels, y_labels;
    DrawNode *drawNode;

};



#endif /* defined(__testproj__LineChart__) */
