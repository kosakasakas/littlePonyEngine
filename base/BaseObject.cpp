//
//  BaseObject.cpp
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BaseObject.h"
#include "cocos2d.h"

BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
}

bool BaseObject::init() {
    return true;
}

void BaseObject::dump() const{
    CCLOG("this object is not defined dump().");
}