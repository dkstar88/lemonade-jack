//
//  ShopLayer.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-20.
//
//

#include "ShopLayer.h"
#include "GameVars.h"
#include "cocostudio/CocoStudio.h"
#include "stdutil.h"
#include "ValueMapMacros.h"

using namespace StringUtils;

ShopListItem* ShopListItem::create(Widget *content, Lemonade::Item* item) {
    ShopListItem* listitem = ShopListItem::create();
    if (listitem) {
        listitem->setLayout(content);
        listitem->setItem(item);
        return listitem;
    }
    return NULL;
}

Lemonade::Item* ShopListItem::getItem() {
    return _item;
}

void ShopListItem::setItem(Lemonade::Item* val) {
    _item = val;
    refresh();
}

void ShopListItem::setLayout(Widget *content) {
    addChild(content);
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    //content->setSize(Size(visibleSize.width, visibleSize.height - 100 - 80));
    content->setVisible(true);
    content->setPosition(Point(0, 0));
    
    icon = SEEK_WIDGET(ImageView*, content, "icon");
    name = SEEK_WIDGET(Text*, content, "name");
    desc = SEEK_WIDGET(Text*, content, "desc");
    price = SEEK_WIDGET(Text*, content, "price");
    count = SEEK_WIDGET(Text*, content, "count");
//    content->setTouchEnabled(true);
    ASSOC_BUTTON(buyOne, content, "btnBuyOne", ShopListItem::buyTouchEvent);
    ASSOC_BUTTON(buyTen, content, "btnBuyTen", ShopListItem::buyTouchEvent);
    buyOne->setLocalZOrder(30);
    buyOne->setTitleColor(Color3B(33, 33, 33));
    buyTen->setTitleColor(Color3B(33, 33, 33));
    
    setSize(content->getSize());
}

void ShopListItem::buyTouchEvent(cocos2d::Ref *pSender, TouchEventType type) {
    if (type==TouchEventType::ENDED) {
        if (pSender == buyOne) {
             _PLAYER_->buy(_item->getName(), 1);
        } else if (pSender == buyTen) {
            _PLAYER_->buy(_item->getName(), 10);
        }
    }
    refresh();
}


bool ShopListItem::init() {
    if (!Layout::init()) {
        return false;
    }
//    scheduleUpdate();
    return true;
}

void ShopListItem::update(float fDelta) {
    refresh();
}

void ShopListItem::refresh() {
    if (!_item) {
        return;
    }
    
    if (icon) {
        icon->loadTexture(_item->getIcon());
    }
    
    if (name) {
        name->setString(_item->getName());
        name->setColor(Color3B(33, 33, 33));
    }
    
    if (desc) {
        desc->setString(_item->getDesc());
    }
    
    if (price) {
        price->setString(format("$%5.2f", _item->getPrice()));
    }
    
    if (count) {
        auto i = _PLAYER_->getInventory()->get(_item->getName());
        if (i) {
            count->setString(format("%d", (int)i->getCount()));
        } else {
            count->setString("0");
        }
    }
    
    if (buyOne) {
        bool enabled = _PLAYER_->canBuy(_item->getName(), 1);
        buyOne->setEnabled(enabled);
        buyOne->setOpacity(enabled ? 255 : 80);
    }
//    buyOne->addTouchEventListener(CC_CALLBACK_2(ShopListItem::buyTouchEvent, this));
    if (buyTen) {
        buyTen->setEnabled(_PLAYER_->canBuy(_item->getName(), 10));
        buyTen->setOpacity(buyTen->isEnabled() ? 255 : 80);
    }
}


// *** ShopLayer *** //
bool ShopLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size sz = Director::getInstance()->getVisibleSize();
//    auto _player = GlobalVars::getPlayer();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    ADD_JSON_WIDGET("studio/shop.ExportJson");
    
    auto content = SEEK_WIDGET(Widget*, widget, "content");
    content->setSize(Size(sz.width, sz.height-200));
    content->setPosition(Point(0, 100));
    listview = SEEK_WIDGET(ListView*, widget, "shop_items");
    
//    auto param = RelativeLayoutParameter::create();
//    param->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
//    param->setMargin(Margin(100, 0, 0, 0));
//    content->setLayoutParameter(param);
    
    sz.height -= 280;
    listview->setSize(sz);
    
    
//    listview = dynamic_cast<ListView *>(Helper::seekWidgetByName(widget, "shop_items"));
    listview->setDirection(ListView::Direction::VERTICAL);
    item_template = SEEK_WIDGET(Layout*, widget, "item");
//    item_template = dynamic_cast<Layout *>(Helper::seekWidgetByName(widget, "item"));
    item_template->setVisible(false);
    sz = item_template->getSize();
    sz.width = visibleSize.width-10;
    item_template->setSize(sz);
    item_template->retain();
    widget->removeChild(item_template);
//    this->schedule(schedule_selector(ShopLayer::UpdateUI));
    refresh();
    return true;
}

void ShopLayer::UpdateUI(float delta) {
    refresh();
}

ShopListItem* ShopLayer::find(Lemonade::Item* item) {
    for (auto listitem: listview->getItems() ) {
        try {
            ShopListItem *itemlistitem = dynamic_cast<ShopListItem *>(listitem);
            if (itemlistitem->getItem() == item) {
                return itemlistitem;
            }
        } catch(std::bad_cast exp) {
            // do nothing
        }

    }
    return NULL;
}

void ShopLayer::refresh() {
    auto _inventory = Lemonade::Inventory::sellerInventory();
    listview->removeAllItems();
    for (auto item: _inventory->getItems()) {
        ShopListItem *itemlistitem = find(item.second);
        if (itemlistitem) {
            // item already added
        } else {
            // item not added
            auto item_temp = item_template->clone();
            itemlistitem = ShopListItem::create(item_temp, item.second);
//            itemlistitem->setSize(item_temp->getSize());
//            itemlistitem->setSize(Size(this->getSize().width, itemlistitem->getSize().height));
//            ((ItemListItemBuy*)itemlistitem)->setPlayer(_player);
            listview->pushBackCustomItem(itemlistitem);
            
        }
//        itemlistitem->refresh();
    }
}