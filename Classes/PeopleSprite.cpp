//
//  PeopleSprite.cpp
//  teaegg
//
//  Created by Yang William Yanzhe on 14-6-9.
//
//

#include "PeopleSprite.h"
#include "cocostudio/cocostudio.h"
#include "SoundUtil.h"
#include "Game.h"



#define PEOPLE_SCREEN_RUN_TIME (20.0f)

std::string PeopleSprite::getEmotion() {
    return _emotion;
}

void PeopleSprite::setEmotion(std::string var) {
    _emotion = var;
    updateAnimation();
}


void PeopleSprite::updateAnimation() {
    std::string plistFile;
    if (_emotion.size()) {
        plistFile = "people/walking-" + _emotion + "/" + _people->getClassname() + ".plist";
    } else {
        plistFile = "people/walking/" + _people->getClassname() + ".plist";
    }
    
    //    std::string textureFile = "people/" + people->getClassname() + ".png";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFile);
    
	Animation *animation = AnimationCache::getInstance()->getAnimation(plistFile);
	if (!animation) {
		Vector<cocos2d::SpriteFrame *> frames;
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistFile);
		ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
		ValueMap _framesMap = dict["frames"].asValueMap();
		std::vector<std::string> frameNames;
		for (auto i : _framesMap) {
			frameNames.push_back(i.first);
		}

		std::sort(frameNames.begin(), frameNames.end());

		for (auto frameName : frameNames) {
			//        CCLOG("Frame: %s", frameName.c_str());
			frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		animation = Animation::createWithSpriteFrames(frames, 0.05f);
		AnimationCache::getInstance()->addAnimation(animation, plistFile);
	}
	
	m_pSprite1->stopAllActions();
	AnimationFrame* firstframe = animation->getFrames().at(0);	
	m_pSprite1->setSpriteFrame(firstframe->getSpriteFrame());
    
    m_pSprite1->runAction( RepeatForever::create( Animate::create(animation) ));
    
    setSize(m_pSprite1->getContentSize());
    
}
bool PeopleSprite::init(Lemonade::People *people) {
    
    if (!Layout::init()) {
        return false;
    }
    setScale(0.5);
    _status = PeopleStatus::Entering;
    _people = people;
    
    m_pSprite1 = Sprite::create();
    m_pSprite1->setAnchorPoint(Point(0.5, 0));
    updateAnimation();
    addChild(m_pSprite1);
    initAnimation();
    this->addTouchEventListener(CC_CALLBACK_2(PeopleSprite::TouchEvent, this));
    return true;
}

PeopleSprite* PeopleSprite::create(Lemonade::People *people) {
    PeopleSprite *ps = new PeopleSprite();
    if (ps->init(people)) {
        return ps;
    } else {
        return NULL;
    }
}

void PeopleSprite::initAnimation() {
    Point startPos, endPos;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    startPos = Point(visibleSize.width, 150);
    endPos = Point(-100, 150);
    setPosition(startPos);
    auto seq = Sequence::create(MoveTo::create(PEOPLE_SCREEN_RUN_TIME/_GAME_SPEED_, endPos), CallFunc::create(CC_CALLBACK_0(PeopleSprite::animFinish, this)), NULL);
    runAction( seq );

}

void PeopleSprite::speech(std::string text, Lemonade::Item* item) {
	auto bbl = SpeechBubble::create();
	bbl->setSpeech(text);
	bbl->setIcon(item->getIcon());
	bbl->setPosition(Point(-20, getSize().height + 20));
	bbl->setGlobalZOrder(50);
	addChild(bbl);
}


void PeopleSprite::animFinish() {
    this->setVisible(false);
}

void PeopleSprite::money_pop(float money) {
     
}

void PeopleSprite::TouchEvent(cocos2d::Ref *pSender, TouchEventType type) {
    if (type == TouchEventType::BEGAN) {
        SoundUtil::playRndSoundAt(this, this->getPeople()->getClassname().c_str());
    }
}