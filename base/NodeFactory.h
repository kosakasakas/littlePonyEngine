//
//  NodeFactory.h
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__GameObjectFactory__
#define __BabylonClicker__GameObjectFactory__

#include "cocos2d.h"
#include "UIFactory.h"

using namespace cocos2d;

class NodeFactory : public Ref
{
public:
    NodeFactory();
    virtual ~NodeFactory();
    virtual bool init();
    CREATE_FUNC(NodeFactory);
    Node* createObject(const ValueMap& valMap);
    UIFactory* getUIFactory();
    
    bool manageChildren(Node* parent, const ValueMap& valMap);
    bool manageColumnNode(const char* column, Node* parent, const ValueMap& valMap);
    
    // containerタグ以下のnodeを生成して返すメソッド
    Node* getContainerNode(const ValueMap& valMap);
private:
    UIFactory* _uif;
};

#endif /* defined(__BabylonClicker__GameObjectFactory__) */
