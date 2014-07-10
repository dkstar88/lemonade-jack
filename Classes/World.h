//
//  World.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#ifndef __lemoname__World__
#define __lemoname__World__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include "People.h"


USING_NS_CC;

namespace Lemonade {
    
        const int WEATHER_SUNNY = 0;
        const int WEATHER_RAIN = 1;
        const int WEATHER_THUNDER = 2;
        const int WEATHER_SNOW = 3;
        
        class World;
        typedef std::vector<World *> Universe;
        
        class World {
        public:
            
			World();
			virtual ~World();

            virtual bool init();
            bool initFromValueMap(ValueMap *map);
            bool initWithName(std::string name);
            CC_SYNTHESIZE(std::string, _name, Name);
            CC_SYNTHESIZE(std::string, _desc, Desc);
            CC_SYNTHESIZE(std::string, _icon, Icon);
            CC_SYNTHESIZE(std::string, _image, Image);
            CC_SYNTHESIZE(float, _price, Price);
            CC_SYNTHESIZE(int, _population, Population);
            CC_SYNTHESIZE(int, _weather, Weather)
            CC_SYNTHESIZE(double, _demand, Demand);
            CC_SYNTHESIZE(int, _money, Money);
//            CC_SYNTHESIZE(int, _reputation, Reputation);
        
            CC_SYNTHESIZE(bool, _locked, Locked);

            float getReputation();
            int sales(Item *item);
            PeopleList* getPeople();
            double getWeatherModifier();
//            void incReputation(int val);
            People* getRandomPeople();
            
//            void enter();
//            void leave();

            static World* create();
            static World* createWithName(std::string name);
            static Universe createWorldList();

            void loadFromValueMap(ValueMap &map);
            void saveToValueMap(ValueMap &map);

        private:
            PeopleList* _people;
            ValueMap people_map;
            bool _has_people_map;
//            CREATE_FUNC(World);
            
        };
    
    
    Universe getUniverse();
    void loadUniverseFromValueMap(Universe& universe, ValueMap& map);
    void saveUniverseToValueMap(Universe& universe, ValueMap& map);
    
}

#endif /* defined(__lemoname__World__) */
