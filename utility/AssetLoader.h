//
//  ObjectFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/18.
//
//

#ifndef __BabylonClicker__PlistLoader__
#define __BabylonClicker__PlistLoader__

#include "cocos2d.h"

class AssetLoader
{
private:
    static AssetLoader* _singleton;
public:
    AssetLoader();
    virtual ~AssetLoader();
    static AssetLoader* getInstatnce();
    cocos2d::Ref* create(const char* fileName, const char* tagName);
};


#endif /* defined(__BabylonClicker__PlistLoader__) */
