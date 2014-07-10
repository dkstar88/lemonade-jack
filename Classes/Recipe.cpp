//
//  Recipe.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#include "Recipe.h"
#include "Item.h"

namespace Lemonade {
    

    Recipe* Recipe::create(ValueMap &map) {
        
        Recipe* recipe = new Recipe();
        recipe->loadFromValueMap(map);
        
        return recipe;
        
    }

    Recipe* Recipe::createWithIngredients(ValueMap &map) {
        
        Recipe* recipe = new Recipe();
        recipe->setIngredients(map);
        
        return recipe;
        
    }
    
    
    Recipe* Recipe::clone() {
        Recipe* recipe = new Recipe();
        recipe->ingredients = IngredientVec(ingredients.begin(), ingredients.end());
        recipe->setMarkup(getMarkup());
//        Ingredient *i = &(*recipe->ingredients.begin());
//        CCLOG("%s: %x", i->item.c_str(), (int)&i);
        return recipe;
    }
    
    double Recipe::getPrice() {
        double price = 0.0f;
        for (auto i: ingredients) {
            Item* item = Item::create(i.item);
            
            price += item->getPrice() * i.amount;
            
            delete item;
        }
        price = round(price * (1.0f+_markup) * 10.0f)/10.0f;
        return price;
    }
    
    Taste& Recipe::getTaste() {
        _taste.reset();
        for (auto i: ingredients) {
            Item* item = Item::create(i.item);
            _taste = _taste + (*item->getTaste() * i.amount);
            delete item;
        }
        return _taste;
    }
    
    void Recipe::setIngredients(ValueMap &map) {
        ingredients.clear();
        for (auto recipe_item: map) {
            // find recipe_item in inventory
            Ingredient ing;
            ValueMap ingmap = recipe_item.second.asValueMap();
            ing.item = recipe_item.first;
            ing.amount = ingmap["amount"].asFloat();
            if (ingmap.find("tweakable") != ingmap.end()) {
                ing.tweakable = ingmap["tweakable"].asBool();
            } else {
                ing.tweakable = false;
            }
            if (ing.tweakable) {
                ing.max = ingmap["max"].asFloat();
                ing.min = ingmap["min"].asFloat();
                ing.step = ingmap["step"].asFloat();
            }
            
            //                CCLOG("%s: %x", ing.item.c_str(), (int)&ing);
            ingredients.push_back(ing);
        }
    }
    
    void Recipe::loadFromValueMap(ValueMap &map) {

        if (map.find("markup") != map.end()) {
            setMarkup(map["markup"].asFloat());
        } else {
            _markup = 0.2;
        }
        if (map.find("ingredients") != map.end()) {
            setIngredients(map["ingredients"].asValueMap());
        } else {
            ingredients.clear();
        }
    }
    
    void Recipe::saveToValueMap(ValueMap &map) {
        ValueMap ingredientsMap;
        for (auto i: ingredients) {
            ValueMap ingData;
            ingData["item"] = i.item;
            ingData["amount"] = i.amount;
            ingData["tweakable"] = i.tweakable;
            if (i.tweakable) {
                ingData["max"] = i.max;
                ingData["min"] = i.min;
                ingData["step"] = i.step;
            }
            ingredientsMap[i.item] = ingData;
        }
        map["ingredients"] = ingredientsMap;
        map["markup"] = getMarkup();
    }
    
    IngredientVec& Recipe::getIngredients() {
        return ingredients;
    }
    
    static RecipesMap _recipes;
    
    RecipesMap& Recipes::getRecipes() {
        return _recipes;
    }
    
    Recipe* Recipes::getRecipe(std::string recipe_name) {
        if (_recipes.find(recipe_name) != _recipes.end()) {
            return &_recipes[recipe_name];
        } else {
            Item* item = Item::create(recipe_name);
            if (item->getRecipe()) {
                _recipes[recipe_name] = *item->getRecipe()->clone();
                return &_recipes[recipe_name];
            }
        }
        return NULL;
    }
    
    void Recipes::setRecipe(std::string recipe_name, Recipe* recipe) {
        _recipes[recipe_name] = *recipe;
    }

    void Recipes::loadFromValueMap(ValueMap &map) {
        _recipes.clear();
        for (auto iter: map) {
            ValueMap recipe_data = map[iter.first].asValueMap();
            Recipe* recipe = Recipe::create(recipe_data);
            _recipes[iter.first] = *recipe;
        }
    }
    
    void Recipes::saveToValueMap(ValueMap &map) {
        for (auto iter: _recipes) {
            ValueMap recipe_data;
            iter.second.saveToValueMap(recipe_data);
            map[iter.first] = recipe_data;
        }
    }
    
}