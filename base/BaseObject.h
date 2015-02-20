//
//  BaseObject.h
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __LITTLE_PONY_ENGINE__BaseObject__
#define __LITTLE_PONY_ENGINE__BaseObject__

#include "cocos2d.h"

USING_NS_CC;

class BaseObject : public virtual Ref {
public:
    BaseObject();
    virtual ~BaseObject();
    virtual bool init();
    CREATE_FUNC(BaseObject);
    virtual void dump() const;
};

#endif /* defined(__LITTLE_PONY_ENGINE__BaseObject__) */
