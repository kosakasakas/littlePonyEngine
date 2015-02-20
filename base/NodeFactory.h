//
//  NodeFactory.h
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__GameObjectFactory__
#define __BabylonClicker__GameObjectFactory__

#include "cocos2d.h"

using namespace cocos2d;

class NodeFactory : public Ref
{
public:
    NodeFactory();
    virtual ~NodeFactory();
    virtual bool init();
    CREATE_FUNC(NodeFactory);
    Node* createObject(ValueMap& valMap);
private:
    Node* setProperty(Node* node, ValueMap map);
};

#endif /* defined(__BabylonClicker__GameObjectFactory__) */
