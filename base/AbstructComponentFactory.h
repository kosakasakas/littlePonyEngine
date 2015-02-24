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
    virtual Node* createObject(const ValueMap& defBody, const ValueMap& uiData) = 0;
    CC_SYNTHESIZE_READONLY(Node*, _node, Node);
protected:
    virtual Node* setProperty(const ValueMap& uiData);
    void addChild(Node* child);
};

#endif /* defined(__BabylonClicker__AbstructComponentFactory__) */
