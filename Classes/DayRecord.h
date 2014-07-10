//
//  DayRecord.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#ifndef __teaegg__DayRecord__
#define __teaegg__DayRecord__

#include "cocos2d.h"
#include "Items.h"
#include "World.h"

USING_NS_CC;

namespace Lemonade {
    
    typedef std::map<std::string, float> ItemRecords;
    class DayRecord {
    public:
        
        CC_SYNTHESIZE(int, _day, Day);
        CC_SYNTHESIZE(float, _earned, Earned);
        CC_SYNTHESIZE(float, _spent, Spent);
        CC_SYNTHESIZE(float, _reputation, Reputation);
        CC_SYNTHESIZE(float, _money, Money);
        CC_SYNTHESIZE(int, _diamond, Diamond);
        CC_SYNTHESIZE(std::string, _world, World);
        
        void sold(std::string& item, float count);
        void bought(std::string& item, float count);
        
        ItemRecords& getSoldItems();
        ItemRecords& getBoughtItems();
        
        DayRecord() {
            _day = 0;
            _earned = 0;
            _spent = 0;
            _money = 0;
            _reputation = 0;
            _diamond = 0;
        }
        
        DayRecord(int day) {
            _day = day;
            _earned = 0;
            _spent = 0;
            _money = 0;
            _reputation = 0;
            _diamond = 0;
        }
        
        void loadFromValueMap(ValueMap &map);
        void saveToValueMap(ValueMap &map);
    protected:
        ItemRecords _soldItems, _boughtItems;
    };
    
    class DayRecords {
    public:
        static DayRecord* getDayRecord(int day);
        static void setDayRecord(int day, DayRecord& day_record);
        static void clearAllRecords();
    private:
        static std::string getDataPath();
    };
    
}

#endif /* defined(__teaegg__DayRecord__) */
