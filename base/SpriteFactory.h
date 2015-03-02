//
//  SpriteFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/02.
//
//

#ifndef __BabylonClicker__SpriteFactory__
#define __BabylonClicker__SpriteFactory__

#include "cocos2d.h"
#include "AbstructComponentFactory.h"

using namespace cocos2d;

class SpriteFactory : public AbstructComponentFactory
{
public:
    SpriteFactory();
    virtual ~SpriteFactory();
    CREATE_FUNC(SpriteFactory);
    virtual Node* createObject(const ValueMap& valMap, const ValueMap& uiData);
};

#endif /* defined(__BabylonClicker__SpriteFactory__) */
