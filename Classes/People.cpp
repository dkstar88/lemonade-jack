//
//  People.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-17.
//
//

#include "People.h"
#include <Map>
#include "World.h"

USING_NS_CC;


namespace Lemonade {
    
    
    bool People::init() {
        _classname = "";
//        _money = 100;
        _taste = Taste::create(5, 5, 5, 5, 5);
        return true;
    }
    
    float People::getMoney() {
        if (_world) {
            return _world->getMoney();
        } else {
            return 0.0f;
        }
    }
    TasteResult* People::demand(Item* item) {
        // Has enough money
        float result = 0;
        float price_rate = getMoney()/item->getPrice();
        TasteResult* taste_result = TasteResult::create(*item->getTaste(), *_taste);
        if (price_rate > 1) {
            // Likes the taste
            CCLOG("%s Taste: %s", item->getDescription().c_str(), item->getTaste()->getDescription().c_str());
            switch (taste_result->getScore()) {
                case LIKE_PERFECT:
                    result = 1.5f;
                    break;
                case LIKE_LIKE:
                    result = 0.75f;
                    break;
                case LIKE_OK:
                    result = 0.5f;
                    break;
                case LIKE_DISLIKE:
                    result = 0.1f;
                    break;
                default:
                    break;
            }
            float reputation_mod = 0.5f + (float)getReputation()/100;
            float random = CCRANDOM_0_1()*3;
            float demand_count = price_rate * result * random * reputation_mod;
            if (demand_count > price_rate) {
                demand_count = price_rate;
            }
			taste_result->setDemand((int)demand_count);
            return taste_result;
        } else {
            taste_result->setMessage("too expensive!");
        }
        return taste_result;
    }
    
    void People::setReputation(int var) {
        _reputation = var;
        if (_reputation > 125) {
            _reputation = 125;
        }
    }
    
    int People::getReputation() {
        return _reputation;
    }
    void People::IncRep(int rep) {
        _reputation += rep;
    }
    People* People::create(std::string classname) {
        People* pp = new People();
        ValueMap vmap = FileUtils::getInstance()->getValueMapFromFile("people.plist");
        ValueMap map = vmap[classname].asValueMap();
        pp->setClassname(classname);
        if (pp->initWithMap(&map)) {
            return pp;
            
        } else {
            return NULL;
        }
    }
    
    People* People::createFromValueMap(ValueMap *map) {
        People* pp = new People();
        if (pp->initWithMap(map)) {
            return pp;
            
        } else {
            return NULL;
        }
    }
    
    bool People::initWithMap(ValueMap *map) {
        if (init()) {
            MAP_STR_PROP("name", this, Name);
//            MAP_INT_PROP("money", this, Money);
            MAP_STR_PROP("icon", this, Icon);
            if (map->find("taste") != map->end()) {
                ValueMap tastemap = map->at("taste").asValueMap();
				if (_taste) delete _taste;
                _taste = Taste::createFromValueMap(&tastemap);
            }
            return true;
        } else {
            return false;
        }
    }
    
    bool People::initWithName(std::string name) {
        ValueMap vmap = FileUtils::getInstance()->getValueMapFromFile("people.plist");
        setClassname(name);
        if (vmap.find(name)!=vmap.end()) {
            ValueMap map = vmap[name].asValueMap();
            if (initWithMap(&map)) {
                return true;
            }
        }
        return false;
    }

	People::People()
	{
		_reputation = 0;
		_taste = NULL;
		_world = NULL;
		
	}

	People::~People() {
		if (_taste) delete _taste;

	}
    // PeopleList //
    class PeopleListGroupSortByPop{
    public:
        PeopleList* _peoplelist;
        PeopleListGroupSortByPop(PeopleList* peoplelist): _peoplelist(peoplelist) {
            
        }
        bool operator()(std::string const &t1, std::string const &t2) const{
            return _peoplelist->getGroup(t1)->getDistribution() > _peoplelist->getGroup(t2)->getDistribution();
        }
    };
//
    bool PeopleList::init(int population, ValueMap* distribution, World* world) {

        _people_groups.clear();
        _population = population;
        ValueMap vmap = FileUtils::getInstance()->getValueMapFromFile("people.plist");

        PeopleGroup::RandomRange range;
        float dist_max = 1;
        //std::vector<PeopleGroup*> unsolved_dist_groups;
        range.lower = 0;
        
        // Read group distribution
        int unsolved_count = 0;
        for (auto iter: vmap) {
            
            ValueMap map = iter.second.asValueMap();
            PeopleGroup* peopleGroup = getGroup(iter.first);
            peopleGroup->setWorld(world);
            peopleGroup->setDistribution(0);
            
            if (distribution == NULL) {
                unsolved_count++;
            } else {
                if (distribution->find(iter.first) != distribution->end()) {
                    peopleGroup->setDistribution(distribution->at(iter.first).asDouble());
                    dist_max -= peopleGroup->getDistribution();
                } else {
                    unsolved_count++;
                }
                
            }
            
        }
        
        // Adverage out distribution for unspeicified people group
        for (auto iter: _people_groups) {
            PeopleGroup* peopleGroup = iter.second;
            
            if (!peopleGroup->getDistribution()) {
                peopleGroup->setDistribution(dist_max/unsolved_count);
            } else {
                
            }
            
            range.high = peopleGroup->getDistribution()*_population + range.lower;
            peopleGroup->setRandomRange(range);
            range.lower = range.high;
        }
        
        _groupsByPop = PeopleList::getGroups();
        std::sort(_groupsByPop.begin(), _groupsByPop.end(), PeopleListGroupSortByPop(this));
        
            
#ifdef DEBUG
            for (auto grp: _groupsByPop) {
                CCLOG("%s pop: %d", grp.c_str(), getGroup(grp)->size());
            }
            
#endif

        return true;
    }
    
    std::vector<std::string>& PeopleList::getGroupsByPop() {
        return _groupsByPop;
    }
    
    PeopleGroup* PeopleList::getGroup(std::string group) {

        if (_people_groups.find(group) == _people_groups.end()) {
            _people_groups[group] = PeopleGroup::create(group);
        }
        return _people_groups[group];
    }
    
    std::vector<std::string> PeopleList::getGroups() {
        std::vector<std::string> result;
        ValueMap vmap = FileUtils::getInstance()->getValueMapFromFile("people.plist");
        for (auto iter: vmap) {
            result.push_back(iter.first);
        }
        return result;
    }
    
    
    People* PeopleList::getRandomPeople(std::string group) {
        if (!_people_groups.size()) {
            return NULL;
        }
        if (group.size()) {
            PeopleGroup* people_group = getGroup(group);
            return dynamic_cast<People*>(people_group);
        } else {
            int r = CCRANDOM_0_1()*_population;
            for (auto iter: _people_groups) {
                PeopleGroup::RandomRange rr = iter.second->getRandomRange();
                if (r >= rr.lower && r < rr.high) {
                    return iter.second;
                }
            }
        }
        auto first = _people_groups.begin();
        return first->second;
    }

    void PeopleList::incGroupRep(std::string group, int delta) {
        PeopleGroup* people_group = getGroup(group);
        if (people_group) {
            people_group->setReputation( people_group->getReputation() + delta);
        }
    }
    
    float PeopleList::getAverageRep(std::string group) {
        if (group.size()) {
            CCLOG("Group: %s", group.c_str());
            PeopleGroup* people_group = getGroup(group);
            return people_group->getReputation();
        } else {
            float rep = 0;
            for (auto iter: _people_groups) {
                //CCLOG("Repuation: %5.2f, Distribution: %5.2f", (float)iter.second->getReputation(),
                //       iter.second->getDistribution());
                rep += (float)iter.second->getReputation() * iter.second->getDistribution();
            }
            return rep;
        }
    }
    
    bool PeopleGroup::init() {
        if (!People::init()) {
            return false;
        }
        _distribution = 0;
        return true;
    }
    
    PeopleGroup* PeopleGroup::create(std::string classname) {
        PeopleGroup* pp = new PeopleGroup();
        ValueMap vmap = FileUtils::getInstance()->getValueMapFromFile("people.plist");
        if (vmap.find(classname) != vmap.end()) {
        ValueMap map = vmap[classname].asValueMap();
        
            if (pp->initWithMap(&map)) {
                pp->setClassname(classname);
                return pp;
                
            }
        }
        return NULL;
    }
    
    void PeopleGroup::loadFromValueMap(ValueMap &map) {
        _distribution = map["distribution"].asFloat();
        _random_range.lower = map["random_range_lower"].asInt();
        _random_range.high = map["randome_range_high"].asInt();
    }
    
    void PeopleGroup::saveToValueMap(ValueMap &map) {
        map["distribution"] = _distribution;
        map["random_range_lower"] = _random_range.lower;
        map["randome_range_high"] = _random_range.high;
    }
    
    void PeopleList::loadFromValueMap(ValueMap &map) {
        ValueMap distr_map = map["distribution"].asValueMap();
        init(map["population"].asInt(), &distr_map );
    }
    
    void PeopleList::saveToValueMap(ValueMap &map) {
        ValueMap dist_map;
        for (auto iter: _people_groups) {
            dist_map[iter.first] = iter.second->getDistribution();
        }
        map["distribution"] = dist_map;
        map["population"]  = _population;
    }
    
}