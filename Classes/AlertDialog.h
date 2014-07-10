//
//  AlertDialog.h
//  Lemonade-Jack
//
//  Created by Yang William Yanzhe on 14-7-4.
//
//

#ifndef __Lemonade_Jack__AlertDialog__
#define __Lemonade_Jack__AlertDialog__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocos2d::ui;

class AlertDialog : public cocos2d::LayerColor {
public:
    typedef std::function<bool(Ref*)> ONCLOSE_EVENT;
    typedef std::function<bool(Ref*, std::string)> ONBUTTONPRESSED_EVENT;
    
    static void Alert(std::string _title, std::string _message, std::string _icon = "", ONCLOSE_EVENT _onClose = NULL);
    static void Confirm(std::string _title, std::string _message, std::string _icon = "", ONBUTTONPRESSED_EVENT _onClose = NULL);
    
    
    std::vector<std::string> Buttons;
    virtual bool init() override;
    void updateButtons();
    ONCLOSE_EVENT onClose;
    ONBUTTONPRESSED_EVENT onButtonPressed;
    void addButton(std::string button_caption);
    void setAttribs(std::string _title, std::string _message, std::string _icon = "");
    CREATE_FUNC(AlertDialog);
    
private:
    void doClose(Ref* pSender);
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    
    Button* closebtn;
    ImageView* icon;
    Text *title, *message;
};

#endif /* defined(__Lemonade_Jack__AlertDialog__) */
