//
//  ItemListItem.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-12.
//
//

#include "ItemListItem.h"


inline std::string IntToStr( int n )
{
    std::ostringstream result;
    result << n;
    return result.str();
}

inline std::string FloatToStr( float n )
{
    std::ostringstream result;
    result << n;
    return result.str();
}


ItemListItem* ItemListItem::create(Lemonade::Item* item_)
{
    ItemListItem *pRet = new ItemListItem();
    if (pRet && pRet->init())
    {
        pRet->setItem(item_);
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return pRet;
    }
}

bool ItemListItem::init() {
    if (Layout::init()) {
        
        this->setTag(1);
        
        image = ImageView::create();
        image->setAnchorPoint(Point(0, 0));
        image->setScale(0.5);
//        image->setSizeType(;)
        image->setSize(Size(64, 64));
        image->setPosition(Point(5, -8));
        this->addChild(image);
        
        
        text = Text::create();
        text->setAnchorPoint(Point(0, 0.5));
        text->setFontSize(24);
        text->setPosition(Point(72, 25));
        text->setSize(Size(200, 64));
        this->addChild(text);
        
        setSize(Size(300, 72));
        setBackGroundColor(Color3B(0xCC, 0xCC, 0xCC));
        image->setSize(Size(64, 64));
        text->setSize(Size(text->getContentSize().width, 64));
        
        return true;
//        scheduleUpdate();
    }
    return false;
}

void ItemListItem::refresh() {
    if (_item) {
        image->loadTexture(_item->getIcon());
        text->setString(_item->getName() +" x "+IntToStr(_item->getCount()));
        text->setSize(Size(this->getSize().width-text->getPosition().x, 64));
        image->setVisible(true);
        text->setVisible(true);
    } else {
        image->setVisible(false);
        text->setVisible(false);
    }
}

void ItemListItem::update(float delta) {
    refresh();
}

Lemonade::Item* ItemListItem::getItem() {
    return _item;
}

void ItemListItem::setItem(Lemonade::Item* val) {
    _item = val;
    refresh();
}


// ### ItemListItemBuy ###
ItemListItemBuy* ItemListItemBuy::create(Lemonade::Item* item_) {
    ItemListItemBuy *pRet = new ItemListItemBuy();
    if (pRet && pRet->init())
    {
        pRet->setItem(item_);
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return pRet;
    }
}

bool ItemListItemBuy::init() {
    if (ItemListItem::init()) {
        _buyOne = BlueButton::createWithTitle("Buy 1", 120, 60, CC_CALLBACK_2(ItemListItemBuy::buyTouchEvent, this));
        _buyTen = BlueButton::createWithTitle("Buy 10", 120, 60, CC_CALLBACK_2(ItemListItemBuy::buyTouchEvent, this));
        

        this->addChild(_buyOne);
        this->addChild(_buyTen);
        return true;
    }
    return false;
}

void ItemListItemBuy::refresh() {
    ItemListItem::refresh();
    char buf[200];
    std::string str_price;
    sprintf(buf, "%s - $ %5.2f", _item->getName().c_str(), _item->getPrice());
    str_price = buf;
    text->setString(str_price);
    _buyOne->setEnabled(canBuy(1));
    _buyTen->setEnabled(canBuy(10));
    _buyOne->setPosition(Point(this->getSize().width-220, 20));
    _buyTen->setPosition(Point(this->getSize().width-100, 20));
}

void ItemListItemBuy::buyTouchEvent(cocos2d::Ref *pSender, TouchEventType type) {
    if (type==TouchEventType::ENDED) {
        if (pSender == _buyOne) {
            buy(1);
        } else if (pSender == _buyTen) {
            buy(10);
        }
    }
}

bool ItemListItemBuy::canBuy(int sales) {
    return (_player && _player->canBuy(_item->getName(), sales));
}

void ItemListItemBuy::buy(int sales) {
    if (_player) {
        _player->buy(_item->getName(), sales);
    }
    refresh();
}

bool ItemListItemBuy::getShowBuyOne() {
    return _showBuyOne;
}

bool ItemListItemBuy::getShowBuyTen() {
    return _showBuyTen;
}

void ItemListItemBuy::setShowBuyOne(bool var) {
    _showBuyOne = var;
    _buyOne->setVisible(_showBuyOne);
}

void ItemListItemBuy::setShowBuyTen(bool var) {
    _showBuyTen = var;
    _buyTen->setVisible(_showBuyTen);
}
