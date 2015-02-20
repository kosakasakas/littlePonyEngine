//
//  NodeFactory.cpp
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "NodeFactory.h"
#include "UIFactory.h"

NodeFactory::NodeFactory()
{
}

NodeFactory::~NodeFactory()
{
}

Node* NodeFactory::createObject(ValueMap& valMap)
{
    // 親Nodeの初期化
    Node* node = Node::create();
    node->setPosition(Vec2(0,0));
    node->setAnchorPoint(Vec2(0,0));
    Size winsize = Director::getInstance()->getWinSize();
    node->setContentSize(winsize);
    node->setScale(1.0);
    
    ValueVector children = valMap.at("children").asValueVector();
    for (Value child : children) {
        ValueMap childMap = child.asValueMap();
        std::string type = childMap.at("type").asString();
        
        UIFactory* uif = UIFactory::create();
        if (type == "button") {
            std::string def = childMap.at("def").asString();
            Menu* menu = uif->createObject("button", def);
            
            setProperty(menu, childMap);
            
            node->addChild(menu);
        } else if (type == "label") {
            std::string def = childMap.at("def").asString();
            LabelTTF* label = uif->createObject("label", def);
            
            setProperty(label, childMap);
            
            node->addChild(label);
        } else {
            CCLOG("can not find node type.");
            node->release();
            node = NULL;
        }
    }
    return node;
}

Node* NodeFactory::setProperty(Node* node, ValueMap map) {
    float pos_x = map.at("pos_x").asFloat();
    float pos_y = map.at("pos_y").asFloat();
    float anchor_x = map.at("anchor_x").asFloat();
    float anchor_y = map.at("anchor_y").asFloat();
    float scale = map.at("scale").asFloat();
    int tag = map.at("tag").asInt();
    int order = map.at("order").asInt();
    
    node->setPosition(Vec2(pos_x, pos_y));
    node->setAnchorPoint(Vec2(anchor_x, anchor_y));
    node->setScale(scale, scale);
    node->setTag(tag);
    node->setZOrder(order);
    
    return node;
}


bool NodeFactory::init() {
    return true;
}