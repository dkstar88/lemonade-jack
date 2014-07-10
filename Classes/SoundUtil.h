//
//  SoundUtil.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-1.
//
//

#ifndef __Lemonade_Jack__SoundUtil__
#define __Lemonade_Jack__SoundUtil__

#include "cocos2d.h"

USING_NS_CC;

class SoundUtil {
public:
    // typedef std::function<bool(const char* currentFile, float percentage)> PreloadCallback;
    static void preloadSounds(const char* plistFile);
    static void playSoundAt(Point position, const char* soundFile);
    static void playSoundAt(Node *node, const char* soundFile);
    static void playRndSoundAt(Node *node, const char* group);
};

#endif /* defined(__Lemonade_Jack__SoundUtil__) */
