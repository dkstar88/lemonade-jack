//
//  SoundUtil.cpp
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-1.
//
//

#include "SoundUtil.h"
#include "ValueMapMacros.h"

std::map<std::string, std::vector<std::string>> _SoundGroupCache;

void SoundUtil::preloadSounds(const char* plistFile) {
    
    ValueMap plist = FileUtils::getInstance()->getValueMapFromFile(plistFile);
    
    for (auto iter: plist) {
        ValueVector values = iter.second.asValueVector();
        for (auto v: values) {
            _SoundGroupCache[iter.first].push_back(v.asString());
            std::string sound = "sfx/" + v.asString();
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sound.c_str());
        }
        
    }
    
}

void SoundUtil::playRndSoundAt(Node *node, const char* group) {
    std::vector<std::string> cacheFiles =_SoundGroupCache[group];
    int r = CCRANDOM_0_1()*cacheFiles.size();
    std::string rndSound = "sfx/" + cacheFiles[r];
    SoundUtil::playSoundAt(node, rndSound.c_str());
}

void SoundUtil::playSoundAt(cocos2d::Node *node, const char *soundFile) {
    Point pos = node->getPosition();
    pos = node->convertToWorldSpace(pos);
    SoundUtil::playSoundAt(pos, soundFile);
}

void SoundUtil::playSoundAt(Point position, const char* soundFile) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point earPos = Point(visibleSize.width/2, visibleSize.height/2);
    
    float dist = earPos.distance(position);
    float distX = position.x - earPos.x;
    float pan = distX/(visibleSize.width/2);
    float gain = 1.0f - (dist * 0.003);
    if (gain < 0.0f) gain = 0.0f;
    if (gain > 1.0f) gain = 1.0f;
    PLAY_SFX(soundFile);
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundFile, false, 1.0f, pan, gain);
}