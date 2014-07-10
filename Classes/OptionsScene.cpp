//
//  OptionsScene.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-2.
//
//

#include "OptionsScene.h"
#include "CCUIUtil.h"

cocos2d::Scene* OptionsLayer::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionsLayer::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool OptionsLayer::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    ADD_JSON_WIDGET("studio/options.ExportJson");
    txtMusicVol = SEEK_WIDGET(TextBMFont*, widget, "txtMusicVol");
    txtSFXVol = SEEK_WIDGET(TextBMFont*, widget, "txtSFXVol");


    
    musicSlider = SEEK_WIDGET(Slider*, widget, "music_volume_slider");
    
    musicSlider->addEventListener(CC_CALLBACK_2(OptionsLayer::onMusicVolumeChanged, this));
    musicSlider->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()*100);
    
    sfxSlider = SEEK_WIDGET(Slider*, widget, "sfx_volume_slider");
    sfxSlider->addEventListener(CC_CALLBACK_2(OptionsLayer::onSfxVolumeChanged, this));
    sfxSlider->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()*100);
    
    txtMusicVol->setString(StringUtils::format("%d%%", musicSlider->getPercent()));
    txtSFXVol->setString(StringUtils::format("%d%%", sfxSlider->getPercent()));
    
    GUIUtil::EnumWidgets(widget, [](Widget* widget) {
        TextBMFont* bmtext = dynamic_cast<TextBMFont*>(widget);
        if (bmtext) bmtext->setFntFile("fonts/marker.fnt");
        return true;
    });
    
    Button* closeButton;
    ASSOC_BUTTON(closeButton, widget, "btnClose", OptionsLayer::TouchEvent)
    
    return true;
    
}

void OptionsLayer::onMusicVolumeChanged(Ref* pSender, Slider::EventType type) {
    txtMusicVol->setString(StringUtils::format("%d%%", musicSlider->getPercent()));
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)musicSlider->getPercent()/100);
}

void OptionsLayer::onSfxVolumeChanged(Ref* pSender, Slider::EventType type) {
    txtSFXVol->setString(StringUtils::format("%d%%", sfxSlider->getPercent()));
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)sfxSlider->getPercent()/100);
}

void OptionsLayer::TouchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    Director::getInstance()->popScene();
}
