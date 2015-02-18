//
//  UCScrollView.h
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#ifndef __BabylonClicker__UCScrollView__
#define __BabylonClicker__UCScrollView__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CustomScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UCScrollView : public CustomScrollView {
public:
    UCScrollView(Menu* menu);
    virtual ~UCScrollView(){};
    static UCScrollView* create(Menu* menu);
    static UCScrollView* create(Size size, Node* container, Menu* menu);
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    enum {
        kUCScrollViewPriority = -129
    };
private:
    virtual bool init();
    virtual void addTouchListener();
    void setMenu(Menu *menu);
    static const float MIN_DISTANCE;
    Point pressPoint;
    Menu *menu;
    bool waitingTouchEnd;
};

#endif /* defined(__BabylonClicker__UCScrollView__) */
