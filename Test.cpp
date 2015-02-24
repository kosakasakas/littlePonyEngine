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
    bool res = true;
    
    AssetLoader* assetLoader = AssetLoader::getInstatnce();
    Ref* a = assetLoader->create("test.plist", "opening");
    
    return res;
}

void BaseObject::dump() const{
    CCLOG("this object is not defined dump().");
}