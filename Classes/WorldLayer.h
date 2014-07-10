//
//  WorldLayer.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#ifndef __lemoname__WorldLayer__
#define __lemoname__WorldLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "World.h"
#include "Items.h"
#include "ItemListView.h"
#include "TopBar.h"

USING_NS_CC;

using namespace Lemonade;
using namespace cocos2d::ui;

class WorldLayer : public cocos2d::Layer {
public:
    virtual bool init() override;
    
    CC_PROPERTY(Lemonade::World*, _world, World);
    
    CREATE_FUNC(WorldLayer);
protected:
    
    ImageView* image;
    Text *title, *desc;
    
    
};

#endif /* defined(__lemoname__WorldLayer__) */
