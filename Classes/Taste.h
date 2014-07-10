//
//  Taste.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#ifndef __lemoname__Taste__
#define __lemoname__Taste__

#include "cocos2d.h"
#include "ValueMapMacros.h"

USING_NS_CC;

namespace Lemonade {
    
    enum LIKE_SCORE {
        LIKE_PERFECT,
        LIKE_LIKE,
        LIKE_OK,
        LIKE_DISLIKE,
    };
    

    class Taste {
    public:
        
        SYNTHESIZE_MAXMIN(_sweet, Sweet, -1, 1);
        SYNTHESIZE_MAXMIN(_sour, Sour, -1, 1);
        SYNTHESIZE_MAXMIN(_bitter, Bitter, -1, 1);
        SYNTHESIZE_MAXMIN(_spicy, Spicy, -1, 1);
        SYNTHESIZE_MAXMIN(_creamy, Creamy, -1, 1);
        
        bool init();
        Taste& operator+(Taste& a);
        Taste& operator+(Taste* a);
        Taste& operator-(Taste& a);
        Taste& operator*(int multipier);
        Taste& operator*(float multipier);
        
        
        Taste* operator/(Taste& a);
        LIKE_SCORE like(Taste* anotherTaste);
        
        float sum();
        Taste* clone();
        
        void reset() {
            _sweet = 0;
            _sour = 0;
            _bitter = 0;
            _spicy = 0;
            _creamy = 0;
        }
        
        static Taste* create(float sweet, float sour, float bitter, float spicy, float creamy) {
            Taste* res = new Taste();
            if (res->init()) {
                res->setSweet(sweet);
                res->setSour(sour);
                res->setBitter(bitter);
                res->setSpicy(spicy);
                res->setCreamy(creamy);
                return res;
            } else {
                return NULL;
            }
        }
        
        static Taste* createFromValueMap(ValueMap* map) {
            Taste* res = new Taste();
            if (res->init()) {
                MAP_FLOAT_PROP("sweet", res, Sweet);
                MAP_FLOAT_PROP("sour", res, Sour);
                MAP_FLOAT_PROP("bitter", res, Bitter);
                MAP_FLOAT_PROP("spicy", res, Spicy);
                MAP_FLOAT_PROP("creamy", res, Creamy);
                
                return res;
            } else {
                return NULL;
            }
        }
        
        std::string getDescription() {
            std::string s = "Taste: [";
            s += StringUtils::format("Sweet: %1.1f, ", _sweet);
            s += StringUtils::format("Sour: %1.1f, ", _sour);
            s += StringUtils::format("Bitter: %1.1f", _bitter);
            s += "]";
            return s;
        }
        
    };
    
    class TasteResult {
    public:
        CC_SYNTHESIZE(LIKE_SCORE, _score, Score);
        CC_SYNTHESIZE(std::string, _message, Message);
        CC_SYNTHESIZE(int, _demand, Demand);
        static TasteResult* create(Taste& taste, Taste& compare_to);
    private:
        float _sweet, _sour, _bitter;
    };
    
}

#endif /* defined(__lemoname__Taste__) */
