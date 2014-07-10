//
//  SpeechBubble.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-9.
//
//

#include "SpeechBubble.h"
#include "ValueMapMacros.h"


bool SpeechBubble::init() {
    if (!Layout::init()) {
        return false;
    }
    
    ADD_JSON_WIDGET("studio/speech.ExportJson");
    
    _bubble = SEEK_WIDGET(Layout*, widget, "speech_bubble");
//    _iconView = SEEK_WIDGET(ImageView*, widget, "icon");
    _speechText = SEEK_WIDGET(Text*, widget, "speech");
    
    return true;
}

std::string SpeechBubble::getIcon() {
    return _icon;
}

std::string SpeechBubble::getSpeech() {
    return _speech;
}

void SpeechBubble::setIcon(std::string var) {
    _icon = var;
//    if (_iconView) {
//        _iconView->loadTexture(_icon);
//    }
}

void SpeechBubble::setSpeech(std::string var) {
    _speech = var;
    if (_speechText ) {
        _speechText->setString(_speech);
        Size sz = _bubble->getSize();
        sz.width = _speechText->getContentSize().width + 40;
        sz.height = 80;
        _bubble->setSize(sz);
        setSize(sz);
    }
}