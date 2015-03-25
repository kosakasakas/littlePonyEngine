//
//  LPScrollableMenu.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/11.
//
//

#include "LPScrollableMenu.h"

//LPScrollableLayerよりも優先度落とす。
#define SCROLLABLE_MENU_PRIORITY -127

LPScrollableMenu::LPScrollableMenu(){
    
}

LPScrollableMenu::~LPScrollableMenu(){
    
}

LPScrollableMenu* LPScrollableMenu::createWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    LPScrollableMenu *pRet = new LPScrollableMenu();
    if (pRet && pRet->initWithArray(arrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

void LPScrollableMenu::onEnter() {
    Menu::onEnter();
    addTouchListener();
}

bool LPScrollableMenu::onTouchBegan(Touch *touch, Event *event) {
    if (!validTouchRectInWorldSpace.size.width || !validTouchRectInWorldSpace.size.height) {
        return Menu::onTouchBegan(touch, event);
    }
    
    Point touchLocation = touch->getLocation();
    if (!validTouchRectInWorldSpace.containsPoint(touchLocation)) {
        return false;
    }
    
    return Menu::onTouchBegan(touch, event);
}

void LPScrollableMenu::onTouchMoved(Touch *touch, Event *event) {
    Menu::onTouchMoved(touch, event);
}

void LPScrollableMenu::onTouchEnded(Touch *touch, Event *event) {
    Menu::onTouchEnded(touch, event);
}

void LPScrollableMenu::onTouchCancelled(Touch *touch, Event *event) {
    Menu::onTouchCancelled(touch, event);
}

void LPScrollableMenu::addTouchListener() {
    auto dispatcher = getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(isSwallowsTouches());
    listener->onTouchBegan = CC_CALLBACK_2(LPScrollableMenu::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LPScrollableMenu::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LPScrollableMenu::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(LPScrollableMenu::onTouchCancelled, this);
    dispatcher->addEventListenerWithFixedPriority(listener, SCROLLABLE_MENU_PRIORITY);
}