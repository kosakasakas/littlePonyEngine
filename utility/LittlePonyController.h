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
#include "UIDefMap.h"

class LittlePonyController
{
public:
    LittlePonyController();
    virtual ~LittlePonyController();
    static LittlePonyController* getInstatnce();
    cocos2d::Ref* getData(const char* fileName, const char* tagName);
    bool init();
    CC_SYNTHESIZE_READONLY(UIDefMap*, _uiDefMap, UIDefMap);
private:
    static LittlePonyController* _singleton;
};


#endif /* defined(__BabylonClicker__PlistLoader__) */
