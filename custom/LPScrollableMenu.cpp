//
//  LPScrollableMenu.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/11.
//
//

#include "LPScrollableMenu.h"

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