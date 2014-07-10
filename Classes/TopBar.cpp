//
//  TopBar.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-18.
//
//

#include "TopBar.h"
#include "cocostudio/CocoStudio.h"
#include "stdutil.h"
#include "GameVars.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "InAppPurchase.h"
#endif
#include "CCUIUtil.h"
#include "Game.h"
#include "AlertDialog.h"

using namespace StringUtils;

bool TopBar::init()
{
    if (!Layout::init()) {
        return false;
    }

    //    Size visibleSize = Director::getInstance()->getVisibleSize();
    _player = _PLAYER_;
    setSize(Director::getInstance()->getVisibleSize());
    Widget* widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(
        "studio/topbar.ExportJson");
    addChild(widget);

    auto layout = RelativeLayoutParameter::create();
    layout->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
    setLayoutParameter(layout);
    //    widget->setPosition(Point(0,
    // visibleSize.height-widget->getSize().height));

    txtDay = SEEK_WIDGET(Text*, widget, "day");
    txtTime = SEEK_WIDGET(Text*, widget, "time");

    txtMoney = SEEK_WIDGET(TextBMFont*, widget, "money");
    txtReputation = SEEK_WIDGET(TextBMFont*, widget, "reputation");
    txtDiamond = SEEK_WIDGET(TextBMFont*, widget, "diamond");
    txtSpeed = SEEK_WIDGET(TextBMFont*, widget, "speed");

    
    // Speed control disabled for now
    auto speed_panel = SEEK_WIDGET(Widget*, widget, "speed_controller");
    speed_panel->setVisible(false);
    
    GUIUtil::SetFntToAll(widget, "fonts/marker.fnt");

    ASSOC_TOUCHEVENT(widget, "add_money", TopBar::AddMoneyTouchEvent);
    ASSOC_TOUCHEVENT(widget, "add_diamond", TopBar::AddDiamondTouchEvent);
    ASSOC_TOUCHEVENT(widget, "change_speed", TopBar::ChangeSpeedTouchEvent);

    this->schedule(schedule_selector(TopBar::UpdateUI), 0.2);

    return true;
}

void TopBar::UpdateUI(float delta) {
    refresh(); }

void TopBar::refresh()
{
    if (_player) {
        if (txtMoney) {
            txtMoney->setString(format("%5.2f", _player->getMoney()->getCount()));
        } else {
            //            txtMoney->setText("");
        }
        if (txtReputation) {
            txtReputation->setString(format("%d", _player->getReputation()));
        } else {
            //            txtReputation->setText("");
        }
        if (txtTime) {
            txtTime->setString(timeToStr(_player->getTime()));
        } else {
            //            txtTime->setText("8:00 PM");
        }
        if (txtDay) {
            txtDay->setString(format("Day %d", _player->getDay()));
        } else {
            //            txtDay->setText("Day 1");
        }
        if (txtSpeed) {
            txtSpeed->setString(
                format("x%d", Lemonade::Game::getInstance().getSpeed()));
        }
        if (txtDiamond) {
            txtDiamond->setString(
                StringUtils::format("%d", (int)_player->getDiamond()->getCount()));
        }
    }
}

void TopBar::AddMoneyTouchEvent(cocos2d::Ref* pSender, TouchEventType type)
{
    if (type==Widget::TouchEventType::ENDED) {
        std::string msg = StringUtils::format(
                                              "Do you want to %d diamonds to %d gold coins?",
                                              _GAME_.getMinDiamondGold(),
                                              _GAME_.getMinDiamondGold() * _GAME_.getGoldPerDiamond());
        AlertDialog::Confirm("Convert Diamond to Gold",
                             msg,
                             "",
                             [](Ref* pSender, std::string button)->bool {
                                 
                                 if (button == "Yes") {
                                     _PLAYER_->buyGold(_GAME_.getMinDiamondGold());
                                 }
                                 return true;
                             });
    }

}

void TopBar::AddDiamondTouchEvent(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (type==Widget::TouchEventType::ENDED) {
        auto dialog = PurchaseDiamondLayer::create();
        //    summaryDialog->onClose = CC_CALLBACK_1(BusinessLayer::onDaySummaryClose,
        // this);
        Director::getInstance()->getRunningScene()->addChild(dialog, 99);
    }
#endif
}

void TopBar::ChangeSpeedTouchEvent(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::ENDED) {
        // TODO: Add Change speed dialog
    }
}
