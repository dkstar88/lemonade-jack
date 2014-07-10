//
//  DayRecord.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-18.
//
//

#include "DayRecord.h"

namespace Lemonade {
    
    void DayRecord::loadFromValueMap(ValueMap &map) {

        _day = map["day"].asInt();
        _earned = map["earned"].asDouble();
        _spent = map["spent"].asDouble();
        _money = map["money"].asFloat();
        _diamond = map["diamond"].asInt();
        _reputation = map["reputation"].asFloat();
        _soldItems.clear();
        if (map.find("sold_items") != map.end()) {
            for (auto iter: map["sold_items"].asValueMap()) {
                _soldItems[iter.first] = iter.second.asInt();
            }
        }
        
        _boughtItems.clear();
        if (map.find("bought_items") != map.end()) {
            for (auto iter: map["bought_items"].asValueMap()) {
                _boughtItems[iter.first] = iter.second.asInt();
            }
        }
        
    }

    void DayRecord::saveToValueMap(ValueMap &map) {
        map["day"] = _day;
        map["earned"] = _earned;
        map["spent"] = _spent;
        map["money"] = _money;
        map["diamond"] = _diamond;
        map["reputation"] = _reputation;
        
        ValueMap soldmap;
        for (auto iter: _soldItems) {
            soldmap[iter.first] = ceil(iter.second);
        }
        map["sold_items"] = soldmap;

        ValueMap boughtmap;
        for (auto iter: _boughtItems) {
            boughtmap[iter.first] = ceil(iter.second);
        }
        map["bought_items"] = boughtmap;
    }
    
    void DayRecord::sold(std::string& item, float count) {
        _soldItems[item]+=count;
    }
    void DayRecord::bought(std::string& item, float count) {
        _boughtItems[item] += count;
    }
    
    ItemRecords& DayRecord::getSoldItems() {
        return _soldItems;
    }
    ItemRecords& DayRecord::getBoughtItems() {
        return _boughtItems;
    }
    
    
    static std::map<int, DayRecord> _day_records;
    
    
    DayRecord* DayRecords::getDayRecord(int day) {
        if (_day_records.find(day) == _day_records.end()) {
            DayRecord* day_rec = new DayRecord(day);
            
            std::string filepath = DayRecords::getDataPath();
            
            if (FileUtils::getInstance()->isFileExist(filepath)) {
                ValueMap data = FileUtils::getInstance()->getValueMapFromFile(filepath);
                std::string strday = StringUtils::format("%d", day);
                if (data.find(strday) != data.end()) {
                    ValueMap daydata = data[strday].asValueMap();
                    day_rec->loadFromValueMap(daydata);
                    _day_records[day] = *day_rec;
                    return &_day_records[day];
                }

            }
            
        } else {
            return &_day_records[day];
        }
        DayRecord* day_rec = new DayRecord(day);
        _day_records[day] = *day_rec;
        return &_day_records[day];
    }
    
    std::string DayRecords::getDataPath() {
        return StringUtils::format("%s/%s", FileUtils::getInstance()->getWritablePath().c_str(), "current/days.plist");
    }
    
    void DayRecords::setDayRecord(int day, DayRecord& day_record) {
        std::string filepath = DayRecords::getDataPath();
        
        std::string strday = StringUtils::format("%d", day);
        ValueMap data = FileUtils::getInstance()->getValueMapFromFile(filepath);

        // Save to plist file
        ValueMap dayMap;
        day_record.saveToValueMap(dayMap);
        data[strday] = dayMap;
            
        FileUtils::getInstance()->writeToFile(data, filepath);
    }
    
    void DayRecords::clearAllRecords() {
        std::string filepath = DayRecords::getDataPath();
        
        if (FileUtils::getInstance()->isFileExist(filepath)) {
            ValueMap emptyDict;
            FileUtils::getInstance()->writeToFile(emptyDict, filepath);
        }
    }

}