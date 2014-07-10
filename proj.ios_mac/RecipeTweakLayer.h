//
//  RecipeTweakLayer.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-13.
//
//

#ifndef __teaegg__RecipeTweakLayer__
#define __teaegg__RecipeTweakLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Lemonade.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;
class Triangle: public DrawNode {
public:
    int length[3] = {30, 60, 45};
    float angle[3] = {CC_DEGREES_TO_RADIANS(90.f), CC_DEGREES_TO_RADIANS(210.f), CC_DEGREES_TO_RADIANS(330.f)};
    virtual bool init() {
        if (!DrawNode::init()) {
            return false;
        }
        
        setContentSize(Size(100, 100));
        setLength(30, 60, 45);
        return true;
    }
    void setLength(int a, int b, int c) {
        clear();
        length[0] = a;
        length[1] = b;
        length[2] = c;
        Size size = getContentSize();
        Point mid = Vec2(size.width, size.height);
        Point points[3];
        for (int i=5; i>0; i--) {
            //            this->drawDot(mid, size.width/5*i, Color4F(0.1*i, 0.1*i, 0.1*i, 200));
            for (int j=0; j<3; j++) {
                points[j] = Point(mid.x + size.width/5*i * cos(angle[j]), mid.y + size.height/5*i * sin(angle[j]));
            }
            drawTriangle(points[0], points[1], points[2], Color4F(0.1*i, 0.2*i, 0.1*i, 0.5));
        }
        
        for (int i=0; i<3; i++) {
            points[i] = Point(mid.x + length[i] * cos(angle[i]), mid.y + length[i] * sin(angle[i]));
        }
        auto red = Color4F(1, 0, 0, 0.5);
        drawTriangle(points[0], points[1], points[2], red);
        //        drawQuadraticBezier(points[0], mid, points[1], 50, red);
        //        drawQuadraticBezier(points[1], mid, points[2], 50, red);
        //        drawQuadraticBezier(points[0], mid, points[2], 50, red);
        
    }
    
    CREATE_FUNC(Triangle);
    
};


class RecipeTweakLayer : public cocos2d::Layer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    CC_PROPERTY(Lemonade::Item*, _target_item, TargetItem);
    
    // implement the "static create()" method manually
    CREATE_FUNC(RecipeTweakLayer);
    Recipe* tweaked_recipe;

    void onRecipeChanged();
    
private:
    
    void addRecipeItem(Lemonade::Ingredient& ing);
    Triangle* _triangle;
    Sprite* _taste_chart_sprite;
    ListView* recipe_items;
    Widget* item_template;
    ImageView* taste_chart;
    
    
};


#endif /* defined(__teaegg__RecipeTweakLayer__) */
