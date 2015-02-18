//
//  UCPlistLoader.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#ifndef __BabylonClicker__UCPlistLoader__
#define __BabylonClicker__UCPlistLoader__

#include "cocos2d.h"

USING_NS_CC;

class UCPlistLoader {
public:
    UCPlistLoader(const char* filePath);
    virtual ~UCPlistLoader();
    Dictionary* getPropertyValueAtIndex(int index) const;
    int getObjectNum() const;
    int getPropertyNum() const;
    Array* getPropertyArray() const;
    void dumpPropertyValueAtIndex(int index) const;
    void dump() const;
    CC_SYNTHESIZE_READONLY(Dictionary*, dictionary, Dictionary);
    static int getInt(Dictionary* dic, const char* key);
    static const char* getChar(Dictionary* dic, const char* key);
    static float getFloat(Dictionary* dic, const char* key);
};

#endif /* defined(__BabylonClicker__UCPlistLoader__) */
