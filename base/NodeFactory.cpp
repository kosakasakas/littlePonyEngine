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
    _uif = UIFactory::create();
    return true;
}

Node* NodeFactory::createObject(const ValueMap& valMap)
{
    // 親Nodeの初期化
    Node* node = Node::create();
    node->setPosition(Vec2(0,0));
    node->setAnchorPoint(Vec2(0,0));
    node->setScale(1.0);
    
    manageChildren(node, valMap);
    
    return node;
}

bool NodeFactory::manageChildren(Node* parent, const ValueMap& valMap) {
    return manageColumnNode("children", parent, valMap);
}

bool NodeFactory::manageColumnNode(const char* column, Node* parent, const ValueMap& valMap) {
    bool hasChildren = (valMap.find(column) != valMap.end());
    if (!hasChildren) {
        return false;
    }
    
    ValueVector children = valMap.at(column).asValueVector();
    for (Value child : children) {
        ValueMap childMap = child.asValueMap();
        const std::string type = childMap.at("type").asString();
        const std::string def = (childMap.find("def") != childMap.end()) ? childMap.at("def").asString() : "uidef not defined";
        Node* uiNode = _uif->createObject(type, def, childMap);
        
        if (uiNode != NULL) {
            parent->addChild(uiNode);
            manageColumnNode(column, uiNode, childMap); // 再帰的に子ノード追加していく
        } else {
            CCLOG("can not find required node.");
        }
    }
    return true;
}

Node* NodeFactory::getContainerNode(const ValueMap& valMap) {
    const char* column = "container";
    bool hasChildren = (valMap.find(column) != valMap.end());
    if (!hasChildren) {
        CCLOG("there is no container!!");
        return NULL;
    }
    
    // containerタグ以下は単体のNodeじゃないと返せない。
    ValueVector children = valMap.at(column).asValueVector();
    if (children.size() != 1) {
        CCLOG("container has to be one object.");
        return NULL;
    }
    
    // rootNodeの生成
    ValueMap childMap = children[0].asValueMap();
    const std::string type = childMap.at("type").asString();
    const std::string def = (childMap.find("def") != childMap.end()) ? childMap.at("def").asString() : "uidef not defined";
    Node* uiNode = _uif->createObject(type, def, childMap);
    
    // children持ちの場合は再帰的にaddChildしていく。
    manageChildren(uiNode, valMap);
    uiNode->retain();
    
    return uiNode;
}

UIFactory* NodeFactory::getUIFactory() {
    return _uif;
}