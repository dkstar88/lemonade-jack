//
//  Taste.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#include "Taste.h"

USING_NS_CC;

namespace Lemonade {
    
    bool Taste::init() {
        _sweet = 0;
        _sour = 0;
        _bitter = 0;
        _spicy = 0;
        _creamy = 0;
        return true;
    }
    
    Taste& Taste::operator +(Taste* a) {
        *this = *this + *a;
        return *this;
    }
    
    Taste& Taste::operator +(Taste& a) {
        
        setSweet(_sweet + a.getSweet());
        setSour(_sour + a.getSour());
        setBitter(_bitter + a.getBitter());
        
        return *this;
    }
    
    Taste& Taste::operator -(Taste& a) {
        setSweet(_sweet - a.getSweet());
        setSour(_sour - a.getSour());
        setBitter(_bitter - a.getBitter());
        return *this;
    }
    
    Taste& Taste::operator *(float multipier) {
        setSweet((multipier*_sweet));
        setSour((multipier*_sour));
        setBitter((multipier*_bitter));
        return *this;
    }
    
    Taste& Taste::operator *(int multipier) {
        setSweet(_sweet * multipier);
        setSour(_sour * multipier);
        setBitter(_bitter * multipier);
        return *this;
    }
    
    Taste* Taste::operator/(Taste& a) {
        Taste* newTaste = this->clone();
        newTaste->setSweet(newTaste->getSweet() / a.getSweet());
        newTaste->setSour(newTaste->getSour() / a.getSour());
        newTaste->setBitter(newTaste->getBitter() / a.getBitter());
        return newTaste;
    }
    
    Taste* Taste::clone() {
        return Taste::create(_sweet, _sour, _bitter, _spicy, _creamy);
    }
    
    float Taste::sum() {
        float r = 0;
        r += getSweet();
        r += getSour();
        r += getBitter();
//        r += getSweet();
//        r += getSweet();
        return r;
    }
    
    LIKE_SCORE Taste::like(Taste* anotherTaste) {
        Taste* taste_result = (*anotherTaste / *this);
        float result = taste_result->sum();

        

        if (result >= 2.5) {
            return LIKE_PERFECT;
        } else if (result >= 2) {
            return LIKE_LIKE;
        } else if (result > 1.5) {
            return LIKE_OK;
        } else {
            return LIKE_DISLIKE;
        }
    }
    
    int compare_taste_result(float &a, float&b) {
        float aa = abs(a);
        float bb = abs(b);

        if (aa > bb) {
            return 1;
        } else if ( aa < bb) {
            return -1;
        } else {
            return 0;
        }
    }
    
    typedef std::pair<float, std::string> TastePair;
    
    bool compare_taste(const TastePair& a, const TastePair& b){
        return a.first > b.first;
    }
    
    TasteResult* TasteResult::create(Taste& taste, Taste& compare_to) {
        TasteResult* result = new TasteResult();
        result->_demand = 0;
        result->_message = "";
        result->_sweet = taste.getSweet() - compare_to.getSweet();
        result->_sour = taste.getSour() - compare_to.getSour();
        result->_bitter = taste.getBitter() - compare_to.getBitter();
        float sum = fabs(result->_sweet) + fabs(result->_sour) + fabs(result->_bitter);
        if (sum < 0.5) {
            result->_score = LIKE_PERFECT;
            result->_message = "Perfect";
        } else if (sum < 1) {
            result->_score = LIKE_LIKE;
            result->_message = "Like";
        } else if (sum < 1.5) {
            result->_score = LIKE_OK;
        } else {
            result->_score = LIKE_DISLIKE;
        }
        
        std::vector<TastePair> tastes;
        if (fabs(result->_sweet) > 0.2)
            tastes.push_back(TastePair(fabs(result->_sweet),
                    (result->_sweet < 0) ? "not sweet enough" : "too sweet"));
        
        if (fabs(result->_sour) > 0.2)
            tastes.push_back(TastePair(fabs(result->_sour),
                                   (result->_sour < 0) ? "not sour enough" : "too sour"));
        
        if (fabs(result->_bitter) > 0.2)
            tastes.push_back(TastePair(fabs(result->_bitter),
                                   (result->_bitter < 0) ? "not bitter enough" : "too bitter"));
        
        sort(tastes.begin(), tastes.end(), compare_taste);
        
        result->_message = "";
        if (tastes.size() > 0) {
            result->_message = tastes.begin()->second;
        }
        
        return result;
    }
    
}