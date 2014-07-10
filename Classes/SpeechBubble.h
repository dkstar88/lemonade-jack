//
//  SpeechBubble.h
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-9.
//
//

#ifndef __teaegg__SpeechBubble__
#define __teaegg__SpeechBubble__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "Player.h"
#include "Refreshable.h"

USING_NS_CC;
using namespace cocos2d::ui;

class SpeechBubble : public Layout {
public:
    virtual bool init();

    CC_PROPERTY(std::string, _speech, Speech);
    CC_PROPERTY(std::string, _icon, Icon);
    
    CREATE_FUNC(SpeechBubble);
    
protected:
    Layout  *_bubble;
    ImageView *_iconView;
    Text *_speechText;
    
    void animFinish();
};

#endif /* defined(__teaegg__SpeechBubble__) */
