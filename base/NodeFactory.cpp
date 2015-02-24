//
//  NodeFactory.cpp
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "NodeFactory.h"
#include "UIFactory.h"

NodeFactory::NodeFactory()
: _uif(NULL)
{
}

NodeFactory::~NodeFactory()
{
}

bool NodeFactory::init() {
    _uif = UIFactory::create("test.plist");
    return true;
}

Node* NodeFactory::createObject(const ValueMap& valMap)
{
    // 親Nodeの初期化
    Node* node = Node::create();
    node->setPosition(Vec2(0,0));
    node->setAnchorPoint(Vec2(0,0));
    Size winsize = Director::getInstance()->getWinSize();
    node->setContentSize(winsize);
    node->setScale(1.0);
    
    manageChildren(node, valMap);
    
    return node;
}

bool NodeFactory::manageChildren(Node* parent, const ValueMap& valMap) {
    bool hasChildren = (valMap.find("children") != valMap.end());
    if (!hasChildren) {
        return false;
    }
    
    ValueVector children = valMap.at("children").asValueVector();
    for (Value child : children) {
        ValueMap childMap = child.asValueMap();
        const std::string type = childMap.at("type").asString();
        const std::string def = childMap.at("def").asString();
        Node* uiNode = _uif->createObject(type, def, childMap);
        
        if (uiNode != NULL) {
            parent->addChild(uiNode);
            manageChildren(uiNode, childMap); // 再帰的に子ノード追加していく
        } else {
            CCLOG("can not find required node.");
        }
    }
    return true;
}