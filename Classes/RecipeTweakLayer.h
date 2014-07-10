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
    int length[3];
    float angle[3];
	virtual bool init();

	void setLength(int a, int b, int c);
    
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
    void IncMarkupTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void DecMarkupTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void addRecipeItem(Lemonade::Ingredient& ing);

	Widget* _content;
    Triangle* _triangle;
    Sprite* _taste_chart_sprite;
    ListView* recipe_items;
    Widget* item_template;
    ImageView* taste_chart;
    
    
};


#endif /* defined(__teaegg__RecipeTweakLayer__) */
