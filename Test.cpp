//
//  Test.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/20.
//
//

#include "Test.h"

Test::Test()
{
}

Test::~Test()
{
}

bool Test::init() {
    return true;
}

bool Test::go() {
    return true;
}

void BaseObject::dump() const{
    CCLOG("this object is not defined dump().");
}