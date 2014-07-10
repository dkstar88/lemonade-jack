//
//  ItemListView.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-13.
//
//

#include "ItemListView.h"

bool ItemListView::init() {
    if (RefreshListView::init()){
//        this->schedule(schedule_selector(ItemListView::UpdateUI), 1, kRepeatForever, 0);
        return true;
    } else {
        return false;
    }
}

void ItemListView::refresh() {
    for (auto item: _inventory->getItems()) {
        ItemListItem *itemlistitem = find(item.second);
        if (itemlistitem) {
            // item already added
        } else {
            // item not added
            itemlistitem = ItemListItemBuy::create(item.second);
            itemlistitem->setSize(Size(this->getSize().width, itemlistitem->getSize().height));
            ((ItemListItemBuy*)itemlistitem)->setPlayer(_player);
            this->addChild(itemlistitem);
        }
        itemlistitem->refresh();
    }
}

ItemListItem* ItemListView::find(Lemonade::Item* item) {
    for (auto listitem: this->getChildren() ) {
        ItemListItem *itemlistitem = (ItemListItem *)listitem;
        if (itemlistitem->getItem() == item) {
            return itemlistitem;
        }
    }
    return NULL;
}