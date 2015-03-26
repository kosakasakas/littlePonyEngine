//
//  ActionFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/26.
//
//

#ifndef __BabylonClicker__ActionFactory__
#define __BabylonClicker__ActionFactory__

#include "cocos2d.h"

using namespace cocos2d;

class ActionFactory : public Ref
{
public:
    ActionFactory();
    virtual ~ActionFactory();
    virtual bool init();
    CREATE_FUNC(ActionFactory);
    virtual Action* createAction(const ValueMap& body);
};

#endif /* defined(__BabylonClicker__ActionFactory__) */
