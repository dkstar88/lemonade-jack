//
//  RecipeTweakLayer.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-13.
//
//

#include "RecipeTweakLayer.h"


class RecipeIngredientLayout: public Layout {
public:
    Lemonade::Ingredient* _ingredient;
    std::string ingredient_name;
    RecipeTweakLayer* recipe_tweak;
    const Lemonade::Ingredient* getIngredient() {
        return _ingredient;
    }
    
    void setIngredient(Lemonade::Ingredient& ing) {
//        CCLOG("setIngredient: %x, %x", (int)_ingredient, (int)&ing);
        _ingredient = &ing;
    }
    
    bool init() override {
        if (!Layout::init()) {
            return false;
        }
        
        return true;
    }
    void setTemplate(Widget* content) {
        addChild(content);
        content->setPosition(Point(0, 0));
        auto incBtn = SEEK_WIDGET(Button*, content, "inc");
        incBtn->addTouchEventListener(CC_CALLBACK_2(RecipeIngredientLayout::IncTouchEvent, this));
        
        auto decBtn = SEEK_WIDGET(Button*, content, "dec");
        decBtn->addTouchEventListener(CC_CALLBACK_2(RecipeIngredientLayout::DecTouchEvent, this));
        
        content->setVisible(true);
        setSize(content->getSize());
    }
    
    void refresh() {
        auto _item = Lemonade::Item::create(_ingredient->item);
        ingredient_name = _ingredient->item;
        if (_item) {
            auto icon = SEEK_WIDGET(ImageView*, this, "icon");
            if (icon) icon->loadTexture(_item->getIcon());
            auto name = SEEK_WIDGET(Text*, this, "name");
            if (name) name->setString(_item->getName());
            auto amount = SEEK_WIDGET(Text*, this, "amount");
            if (amount) amount->setString(StringUtils::format("%2.1f", _ingredient->amount));
            
            
            if (!_ingredient->tweakable) {
                auto incBtn = SEEK_WIDGET(Button*, this, "inc");
                auto decBtn = SEEK_WIDGET(Button*, this, "dec");
                if (incBtn) incBtn->setVisible(false);
                if (decBtn) decBtn->setVisible(false);
            }
        }
        delete _item;
        recipe_tweak->onRecipeChanged();
    }
    
    void IncTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
        if (type==Widget::TouchEventType::ENDED) {
            _ingredient->amount += _ingredient->step;
            refresh();
        }
    }
    void DecTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
        if (type==Widget::TouchEventType::ENDED) {
            _ingredient->amount -= _ingredient->step;
            refresh();
        }
    }
    CREATE_FUNC(RecipeIngredientLayout)
};

bool RecipeTweakLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    
    ADD_JSON_WIDGET("studio/recipe.ExportJson");
	_content = widget;
    recipe_items = SEEK_WIDGET(ListView*, widget, "ingredients");
    item_template = SEEK_WIDGET(Widget*, widget, "ingredient");
    taste_chart = SEEK_WIDGET(ImageView*, widget, "taste_chart");
    auto recipe_icon = SEEK_WIDGET(ImageView*, widget, "recipe_icon");
    recipe_icon->setVisible(false);
    taste_chart->setVisible(false);
    Size size = taste_chart->getSize();
    _triangle = Triangle::create();
    _triangle->setContentSize(size);
    
    Button *incMarkup, *decMarkup;
    ASSOC_BUTTON(incMarkup, widget, "inc_price", RecipeTweakLayer::IncMarkupTouchEvent);
    ASSOC_BUTTON(decMarkup, widget, "dec_price", RecipeTweakLayer::DecMarkupTouchEvent);
    
    auto panel = SEEK_WIDGET(Layout*, widget, "taste_panel");
    this->addChild(_triangle);
//     = panel->getPosition();
    Point _p = panel->getWorldPosition();
    _triangle->setPosition(_p);
//    _triangle->setPosition(_p);
    _triangle->setLocalZOrder(20);
    recipe_items->setDirection(ListView::Direction::VERTICAL);
    item_template->setVisible(false);
    return true;
}

Lemonade::Item* RecipeTweakLayer::getTargetItem() {
    return _target_item;
}

void RecipeTweakLayer::addRecipeItem(Lemonade::Ingredient& ing) {
    
    auto listitem = RecipeIngredientLayout::create();
    listitem->setIngredient(ing);
    listitem->recipe_tweak = this;
    listitem->setTemplate(item_template->clone());
    listitem->refresh();
    recipe_items->pushBackCustomItem(listitem);
}

void RecipeTweakLayer::setTargetItem(Lemonade::Item *var) {
    _target_item = var;
    if (recipe_items) {
        recipe_items->removeAllItems();
        tweaked_recipe = Recipes::getRecipe(_target_item->getName());
        IngredientVec& ingredients = tweaked_recipe->getIngredients();
        for (int i = 0; i < ingredients.size(); i++) {
            Ingredient& it = ingredients[i];
//            CCLOG("addRecipeItem: %x", (int)&ingredients[i]);
            addRecipeItem(it);
        }
        
    }
}

void RecipeTweakLayer::IncMarkupTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type==Widget::TouchEventType::ENDED) {
        tweaked_recipe->setMarkup(tweaked_recipe->getMarkup()+0.1);
        onRecipeChanged();
    }
}
void RecipeTweakLayer::DecMarkupTouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type==Widget::TouchEventType::ENDED) {
        tweaked_recipe->setMarkup(tweaked_recipe->getMarkup()-0.1);
        onRecipeChanged();
    }
}

void RecipeTweakLayer::onRecipeChanged() {
	auto price = SEEK_WIDGET(Text*, _content, "recipe_price");
    if (price) {
        price->setString(StringUtils::format("%5.02f", tweaked_recipe->getPrice()));
    }
    auto _taste = tweaked_recipe->getTaste();
	auto price_markup = SEEK_WIDGET(Text*, _content, "amount_markup");
    if (price_markup) {
        price_markup->setString(StringUtils::format("%d%%", (int)(tweaked_recipe->getMarkup()*100.0)));
    }
    _triangle->setLength(_taste.getSweet()*150, _taste.getSour()*150, _taste.getBitter()*150);
    CCLOG("%s", _taste.getDescription().c_str());
}

bool Triangle::init()
{
	if (!DrawNode::init()) {
		return false;
	}
	
	angle[0] = CC_DEGREES_TO_RADIANS(90.f);
	angle[1] = CC_DEGREES_TO_RADIANS(210.f);
	angle[2] = CC_DEGREES_TO_RADIANS(330.f);

	setContentSize(Size(100, 100));
	setLength(30, 60, 45);
	return true;
}

void Triangle::setLength(int a, int b, int c)
{
	clear();
	length[0] = a;
	length[1] = b;
	length[2] = c;
	Size size = getContentSize();
	Point mid = Vec2(size.width, size.height);
	Point points[3];
	for (int i = 5; i > 0; i--) {
		//            this->drawDot(mid, size.width/5*i, Color4F(0.1*i, 0.1*i, 0.1*i, 200));
		for (int j = 0; j < 3; j++) {
			points[j] = Point(mid.x + size.width / 5 * i * cos(angle[j]), mid.y + size.height / 5 * i * sin(angle[j]));
		}
		drawTriangle(points[0], points[1], points[2], Color4F(0.1*i, 0.2*i, 0.1*i, 0.5));
	}

	for (int i = 0; i < 3; i++) {
		points[i] = Point(mid.x + length[i] * cos(angle[i]), mid.y + length[i] * sin(angle[i]));
	}
	auto red = Color4F(1, 0, 0, 0.5);
	drawTriangle(points[0], points[1], points[2], red);

}