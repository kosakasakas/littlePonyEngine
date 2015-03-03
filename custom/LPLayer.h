//
//  LPLayer.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/03.
//
//

#ifndef __BabylonClicker__LPLayer__
#define __BabylonClicker__LPLayer__

#include "cocos2d.h"
#include "Observer.h"

class LPLayer: public cocos2d::Layer, public Observer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual void onNotice();
};

#endif /* defined(__BabylonClicker__LPLayer__) */
