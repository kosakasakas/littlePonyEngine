//
//  Utility.h
//  UCEngine
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#ifndef __UCEngine__Utility__
#define __UCEngine__Utility__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Utility
{
private:
public:
    static bool isDecimalValue(const char* text);
    static const char* getStrFromFloatValue(float val);
    static int getRandomInt(int limit);
    static const char* getStrFromFloatInt(int val);
};

#endif /* defined(__UCEngine__Utility__) */
