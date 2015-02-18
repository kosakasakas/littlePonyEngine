//
//  UCScrollableMenu.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/09/07.
//
//

#include "UCScrollableMenu.h"

UCScrollableMenu::UCScrollableMenu(){
    
}

UCScrollableMenu::~UCScrollableMenu(){
    
}

UCScrollableMenu* UCScrollableMenu::createWithArray(Array* pArrayOfItems)
{
    UCScrollableMenu *pRet = new UCScrollableMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool UCScrollableMenu::onTouchBegan(Touch *touch, Event *event) {
    if (!validTouchRectInWorldSpace.size.width || !validTouchRectInWorldSpace.size.height) {
        return Menu::onTouchBegan(touch, event);
    }
    
    Point touchLocation = touch->getLocation();
    if (!validTouchRectInWorldSpace.containsPoint(touchLocation)) {
        return false;
    }
    
    return Menu::onTouchBegan(touch, event);
}