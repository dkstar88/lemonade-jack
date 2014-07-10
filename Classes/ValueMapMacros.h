//
//  ValueMapMacros.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-17.
//
//

#ifndef lemoname_ValueMapMacros_h
#define lemoname_ValueMapMacros_h

#include "cocostudio/cocostudio.h"


#define  MAP_FLOAT_PROP(__MAPKEY__, __OBJ__, __METHOD__)   \
if (map->find(__MAPKEY__)!=map->end()){ \
__OBJ__->set##__METHOD__(map->at(__MAPKEY__).asDouble()); \
}

#define  MAP_INT_PROP(__MAPKEY__, __OBJ__, __METHOD__)   \
if (map->find(__MAPKEY__)!=map->end()){ \
__OBJ__->set##__METHOD__(map->at(__MAPKEY__).asInt()); \
}

#define  MAP_STR_PROP(__MAPKEY__, __OBJ__, __METHOD__)   \
if (map->find(__MAPKEY__)!=map->end()){ \
__OBJ__->set##__METHOD__(map->at(__MAPKEY__).asString()); \
}

#define  MAP_FLOAT_PROP_(__MAPKEY__, __OBJ__, __METHOD__)   \
if (map.find(__MAPKEY__)!=map.end()){ \
__OBJ__->set##__METHOD__(map.at(__MAPKEY__).asDouble()); \
}

#define  MAP_INT_PROP_(__MAPKEY__, __OBJ__, __METHOD__)   \
if (map.find(__MAPKEY__)!=map.end()){ \
__OBJ__->set##__METHOD__(map.at(__MAPKEY__).asInt()); \
}

#define  MAP_STR_PROP_(__MAPKEY__, __OBJ__, __METHOD__)   \
if (map.find(__MAPKEY__)!=map.end()){ \
__OBJ__->set##__METHOD__(map.at(__MAPKEY__).asString()); \
}

#define SEEK_WIDGET(__TYPE__, __ROOT__, __NAME__) dynamic_cast<__TYPE__>(Helper::seekWidgetByName(__ROOT__, __NAME__));


#define ASSOC_BUTTON(__VAR__, __ROOT__, __NAME__, __EVENT__) __VAR__ = dynamic_cast<Button*>(Helper::seekWidgetByName(__ROOT__, __NAME__)); \
    __VAR__->setTouchEnabled(true); \
    __VAR__->addTouchEventListener(CC_CALLBACK_2(__EVENT__, this));

#define ADD_JSON_WIDGET(__FILE__) \
Widget *widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(__FILE__); \
addChild(widget);



#define SYNTHESIZE_MAXMIN(varName, funName, minVar, maxVar)\
protected: float varName;\
public: virtual float get##funName(void) const { return varName; }\
public: virtual void set##funName(float var){ varName = std::min<float>(std::max<float>(var, minVar), maxVar); }
#endif

#define ASSOC_TOUCHEVENT(__ROOT__, __NAME__, __EVENT__) (dynamic_cast<Widget*>(Helper::seekWidgetByName(__ROOT__, __NAME__)))->setTouchEnabled(true); \
    (dynamic_cast<Widget*>(Helper::seekWidgetByName(__ROOT__, __NAME__)))->addTouchEventListener(CC_CALLBACK_2(__EVENT__, this));

#define PLAY_SFX CocosDenshion::SimpleAudioEngine::getInstance()->playEffect
#define PLAY_BG CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic

