//
//  ItemListView.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-13.
//
//

#ifndef __lemoname__ItemListView__
#define __lemoname__ItemListView__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items.h"
#include "ItemListItem.h"
#include "RefreshListView.h"


USING_NS_CC;
using namespace cocos2d::ui;

class ItemListView : public RefreshListView {
public:
    virtual bool init() override;
    CC_SYNTHESIZE(Lemonade::Inventory* , _inventory, Inventory);
    CC_SYNTHESIZE(Lemonade::Player*, _player, Player);

    ItemListItem* find(Lemonade::Item* item);
    
    virtual void refresh() override;
    
    static ItemListView* create(Lemonade::Player* player) {
        ItemListView* listview = ItemListView::create();
        if (listview) {
            listview->setPlayer(player);
            listview->setInventory(player->getInventory());
            return listview;
        } else {
            return NULL;
        }
    }
    
//    CREATE_CLASS_WIDGET_READER_INFO(ItemListView);
    CREATE_FUNC(ItemListView);
    
};

#endif /* defined(__lemoname__ItemListView__) */
