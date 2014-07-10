//
//  People.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-17.
//
//

#ifndef __lemoname__People__
#define __lemoname__People__

#include "cocos2d.h"
#include "Item.h"
#include "ValueMapMacros.h"
#include "Taste.h"

USING_NS_CC;

namespace Lemonade {

    class World;

    class People {
    public:
		People();
		virtual ~People();

        virtual bool init();
        bool initWithName(std::string name);
        bool initWithMap(ValueMap *map);
        
        TasteResult* demand(Item* item);
        void IncRep(int rep);
        
        CC_SYNTHESIZE(std::string, _classname, Classname);
        CC_SYNTHESIZE(std::string, _name, Name);
        CC_SYNTHESIZE(std::string, _icon, Icon);
        
        CC_PROPERTY(int, _reputation, Reputation);
        CC_SYNTHESIZE(Taste*, _taste, Taste);
        CC_SYNTHESIZE(World*, _world, World);
        
        float getMoney();
        
        static People* create(std::string classname);
        static People* createFromValueMap(ValueMap *map);
        


    };
    class PeopleGroup: public People {
    public:
        struct RandomRange {
            int lower;
            int high;
        };
        virtual bool init();
        CC_SYNTHESIZE(float, _distribution, Distribution);
        CC_SYNTHESIZE(RandomRange, _random_range, RandomRange);
        void loadFromValueMap(ValueMap &map);
        void saveToValueMap(ValueMap &map);
        static PeopleGroup* create(std::string classname);
    };
    
    typedef std::map<std::string, PeopleGroup*> PeopleGroups;
    
    class PeopleList {
    public:
        CC_SYNTHESIZE(int, _population, Population);
        bool init(int population, ValueMap* distribution = NULL, World* world = NULL);
//        CC_SYNTHESIZE(PeopleListArray, _list, PeopleList);
        PeopleGroup* getGroup(std::string group);
        People* addPeople(People* people);
        People* getRandomPeople(std::string group);
        // Get Average Reputation
        float getAverageRep(std::string group = "");
        bool compare_by_pop(const PeopleGroup* a, const PeopleGroup* b);
        std::vector<std::string>& getGroupsByPop();
        
        void incGroupRep(std::string group, int delta);
        void setWorld(World* world);
        static std::vector<std::string> getGroups();
        
        void loadFromValueMap(ValueMap &map);
        void saveToValueMap(ValueMap &map);
        
        static PeopleList* create(int population, World* world) {
            PeopleList* pplist = new PeopleList();
            if (pplist->init(population, NULL, world)) {
                return pplist;
            } else {
                return NULL;
            }
        }
        
        static PeopleList* create(int population, ValueMap* distribution, World* world) {
            PeopleList* pplist = new PeopleList();
            if (pplist->init(population, distribution, world)) {
                return pplist;
            } else {
                return NULL;
            }
        }
        
    protected:
        PeopleGroups _people_groups;
        std::vector<std::string> _groupsByPop;

    };

}

#endif /* defined(__lemoname__People__) */
