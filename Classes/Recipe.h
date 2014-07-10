//
//  Recipe.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#ifndef __lemoname__Recipe__
#define __lemoname__Recipe__

#include "cocos2d.h"
#include "Taste.h"

USING_NS_CC;



namespace Lemonade {

    struct Ingredient {
        std::string item;
        float amount, min, max;
        float step;
        bool tweakable;
//        static std::size_t count;
//        Ingredient() { ++count; CCLOG("Ingredient Constructing count = %ld\n", count); }
//        ~Ingredient() { --count; CCLOG("Ingredient Destructing count = %ld\n", count); }
    };
    
    typedef std::vector<Ingredient> IngredientVec;
    
    class Recipe  {
    public:
        IngredientVec ingredients;
        IngredientVec& getIngredients();
        CC_SYNTHESIZE(float, _markup, Markup);
        
        static Recipe* create(ValueMap &map);
        static Recipe* createWithIngredients(ValueMap &map);
        
        double getPrice();
        Taste& getTaste();
        Recipe* clone();
        
        void loadFromValueMap(ValueMap &map);
        void saveToValueMap(ValueMap &map);
        void setIngredients(ValueMap &map);
        
        Recipe() {
            _taste = *Taste::create(0, 0, 0, 0, 0);
			_markup = 0.2;
        }
        ~Recipe() {
            
        }
        
    private:
        Taste _taste;
    };
    
    typedef std::map<std::string, Recipe> RecipesMap;
    
    class Recipes {
    public:
        static RecipesMap& getRecipes();
        static Recipe* getRecipe(std::string recipe_name);
        static void setRecipe(std::string recipe_name, Recipe* recipe);
        
        static void loadFromValueMap(ValueMap &map);
        static void saveToValueMap(ValueMap &map);
        
    };
    
}

#endif /* defined(__lemoname__Recipe__) */
