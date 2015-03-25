//
//  LPScrollableMenu.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/11.
//
//

#ifndef __BabylonClicker__LPScrollableMenu__
#define __BabylonClicker__LPScrollableMenu__

#include "cocos2d.h"

USING_NS_CC;

class LPScrollableMenu : public Menu {
public:
    LPScrollableMenu();
    ~LPScrollableMenu();
    static LPScrollableMenu* createWithArray(const Vector<MenuItem*>& arrayOfItems);
    CREATE_FUNC(LPScrollableMenu);
    
    void setValidTouchRectInWorldSpace(Rect rect) { this->validTouchRectInWorldSpace = rect; };
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    virtual void onEnter();
    virtual void onExit();
private:
    Rect validTouchRectInWorldSpace;
    EventListenerTouchOneByOne* _LPScrollableMenuTouchListener;
    
    void addTouchListener();
    void removeTouchListener();
};


#endif /* defined(__BabylonClicker__LPScrollableMenu__) */
