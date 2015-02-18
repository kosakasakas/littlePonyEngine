//
//  UCScrollableMenu.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/09/07.
//
//

#ifndef __BabylonClicker__UCScrollableMenu__
#define __BabylonClicker__UCScrollableMenu__

#include "cocos2d.h"

USING_NS_CC;

class UCScrollableMenu : public Menu {
public:
    UCScrollableMenu();
    ~UCScrollableMenu();
    static UCScrollableMenu* createWithArray(Array* pArrayOfItems);
    CREATE_FUNC(UCScrollableMenu);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    void setValidTouchRectInWorldSpace(Rect rect) { this->validTouchRectInWorldSpace = rect; };
private:
    Rect validTouchRectInWorldSpace;
};


#endif /* defined(__BabylonClicker__UCScrollableMenu__) */
