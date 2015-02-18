//
//  UCAnimation.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/11.
//
//

#ifndef __BabylonClicker__UCAnimation__
#define __BabylonClicker__UCAnimation__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class UCAnimation
{
public:
    static Point getRotatePoint(Point from, float distance, float degree);
    static ActionInterval* getDamageAction(Point from);
    static ActionInterval* getAttackAction(Point from, Point to);
};

#endif /* defined(__BabylonClicker__UCAnimation__) */
