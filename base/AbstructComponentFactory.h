//
//  AbstructComponentFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#ifndef __BabylonClicker__AbstructComponentFactory__
#define __BabylonClicker__AbstructComponentFactory__

#include "cocos2d.h"

using namespace cocos2d;

class AbstructComponentFactory : public Ref
{
public:
    AbstructComponentFactory();
    virtual ~AbstructComponentFactory();
    virtual bool init();
    virtual Node* createObject(const ValueMap& defBody, const ValueMap& uiData);
protected:
    virtual void setProperty(Node* node, const ValueMap& uiData);
};

#endif /* defined(__BabylonClicker__AbstructComponentFactory__) */
