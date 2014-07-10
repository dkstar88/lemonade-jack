//
//  Util.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#ifndef __teaegg__Util__
#define __teaegg__Util__

#include "Items.h"
#include "World.h"
#include "Recipe.h"
#include "People.h"
#include "Game.h"

namespace Lemonade {
    
    inline void printTasteResult(World* world) {
        auto population = world->getPeople();
        auto groups = population->getGroups();
        auto target_item = _PRODUCTION_;
        CCLOG("%s Taste: %s", target_item->getName().c_str(), target_item->getTaste()->getDescription().c_str());
        for (auto grp: groups) {
            auto people = People::create(grp);
            TasteResult* taste_res = TasteResult::create(*target_item->getTaste(), *people->getTaste());
            
            CCLOG("%s >> %s :: %s", target_item->getName().c_str(), grp.c_str(), taste_res->getMessage().c_str());

        }
        CCLOG("----------printTasteResult------------");
    }
    
}
#endif /* defined(__teaegg__Util__) */
