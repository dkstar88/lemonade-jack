//
//  OptionsScene.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-2.
//
//

#ifndef __Lemonade_Jack__OptionsScene__
#define __Lemonade_Jack__OptionsScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Car.h"
#include "PeopleSprite.h"
#include "TrafficLayer.h"


USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class OptionsLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    bool init() override;
    
    CREATE_FUNC(OptionsLayer);
    
private:
    
    void onMusicVolumeChanged(Ref* pSender, Slider::EventType type);
    void onSfxVolumeChanged(Ref* pSender, Slider::EventType type);
    void TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    TextBMFont *txtMusicVol, *txtSFXVol;
    Slider *musicSlider, *sfxSlider;
    
};

#endif /* defined(__Lemonade_Jack__OptionsScene__) */
