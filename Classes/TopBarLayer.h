//
//  TopBarLayer.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#ifndef __lemoname__TopBarLayer__
#define __lemoname__TopBarLayer__

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

class TopBarLayer : public cocos2d::Layer
{
public:
    virtual bool init() override;
    
    CREATE_FUNC(TopBarLayer);
    
private:
    
    TopBar *_topBar;
};

#endif /* defined(__lemoname__TopBarLayer__) */
