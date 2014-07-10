//
//  World.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#include "World.h"
#include "ValueMapMacros.h"


namespace Lemonade {
    
        
    bool World::init() {
        this->_weather = WEATHER_SUNNY;
        this->_population = 1000;
        this->_name = "Neighbourhood";
        this->_demand = 0.2;
//        this->_reputation = 0;
        _has_people_map = false;
//        this->_people = Lemonade::PeopleList::create(_population);
        return true;
    }

    float World::getReputation() {
        return getPeople()->getAverageRep();
    }
    
    PeopleList* World::getPeople() {
        if (!_people) {
            if (_has_people_map) {
                _people = Lemonade::PeopleList::create(_population, &people_map, this);
            } else {
                _people = Lemonade::PeopleList::create(_population, this);
            }
        }
        return _people;
    }

    double World::getWeatherModifier() {
        double result = 1;
        switch (_weather) {
            case WEATHER_SUNNY:
                result = 1.5;
                break;
            case WEATHER_RAIN:
                result = 0.8;
                break;
            case WEATHER_THUNDER:
                result = 0.4;
                break;
                
            case WEATHER_SNOW:
                result = 0.4;
                break;
                
            default:
                break;
        }
        return result;
    }
    
//    void World::incReputation(int val) {
//        _reputation += val;
//        if (_reputation > 100) {
//            _reputation = 100;
//        }
//    }
//    
    int World::sales(Item *item) {
        int base_sales = (item->getDemand() * _population);
        double world_modifier = 1.0 + (CCRANDOM_0_1() * _demand) - (_demand/2);
        double weather_modifier = getWeatherModifier();
        double reputation_modifier = 1; //(getReputation()+10.0)/100;
        return base_sales*world_modifier*weather_modifier*reputation_modifier;
    }
    
    People* World::getRandomPeople() {
        return getPeople()->getRandomPeople("");
    }

    bool World::initFromValueMap(ValueMap *map) {
        MAP_STR_PROP("icon", this, Icon);
        MAP_STR_PROP("desc", this, Desc);
        MAP_STR_PROP("image", this, Image);
        MAP_INT_PROP("weather", this, Weather);
        MAP_INT_PROP("population", this, Population);
        MAP_FLOAT_PROP("price", this, Price);
        MAP_INT_PROP("money", this, Money);
        if (map->find("people") != map->end()) {
            people_map = map->at("people").asValueMap();
            _has_people_map = true;
        }
//            MAP_STR_PROP(name, this, Name);
//            MAP_FLOAT_PROP("demand", this, Demand);
//            if ( map->find("items") != map->end() ) {
//                _itemVar = map->at("items").asValueMap();
//            }
        return true;
    }
    
    bool World::initWithName(std::string name) {
        ValueMap p_vec = FileUtils::getInstance()->getValueMapFromFile("worlds.plist");
        if (p_vec.find(name) != p_vec.end()) {
            _name = name;
            ValueMap data = p_vec[name].asValueMap();
            return this->initFromValueMap(&data);
        }
        return false;
        
    }

    World* World::create() {
        World* world = new World();
        if (world && world->init()) {
            return world;
        } else {
            return NULL;
        }
    }
    
    World* World::createWithName(std::string name) {
        World* world = new World();
        if (world && world->initWithName(name)) {
            return world;
        } else {
            return NULL;
        }
    }
    
    bool compare_world_price(World* a, World* b){
        return a->getPrice() < b->getPrice();
    }
    
    std::vector<World *> World::createWorldList() {
        std::vector<World *> worldlist;
        ValueMap p_vec = FileUtils::getInstance()->getValueMapFromFile("worlds.plist");
        for (auto iter: p_vec) {
            World *w = World::create();
            ValueMap map = iter.second.asValueMap();
            w->setName(iter.first);
            w->initFromValueMap(&map);
            worldlist.push_back(w);
        }
        sort(worldlist.begin(), worldlist.end(), compare_world_price);
        return worldlist;
    }

//    void World::enter() {
//        _locked = false;
//        delete _people;
//        _people = PeopleList::create(_population, &people_map, this);
//    }
//    
//    void World::leave() {
//        delete _people;
//    }

	World::World()
	{
		_people = NULL;
	}

	World::~World() {
		if (_people) delete _people;
	}

    void World::loadFromValueMap(ValueMap &map) {
        ValueMap people_list_map = map["people_list"].asValueMap();
        getPeople()->loadFromValueMap(people_list_map);
    }
    
    void World::saveToValueMap(ValueMap &map) {
        ValueMap people_list_map;
        getPeople()->saveToValueMap(people_list_map);
        map["people_list"] = people_list_map;
    }
    
    Universe getUniverse() {
        return World::createWorldList();
    }
    
    void loadUniverseFromValueMap(Universe& universe, ValueMap& map) {
        if (map.find("worlds") != map.end()) {
            ValueMap worlds_map = map["worlds"].asValueMap();
            
            for (auto world: universe) {
                if (worlds_map.find(world->getName()) != worlds_map.end()) {
                    ValueMap world_map = worlds_map[world->getName()].asValueMap();
                    world->loadFromValueMap(world_map);
                }
            }
        }
    }
    
    void saveUniverseToValueMap(Universe& universe, ValueMap& map) {
        ValueMap worlds_map;
        for (auto world: universe) {
           ValueMap world_map_val;
            world->saveToValueMap(world_map_val);
            worlds_map[world->getName()] = world_map_val;
            
        }
        map["worlds"] = worlds_map;
    }
        
}
