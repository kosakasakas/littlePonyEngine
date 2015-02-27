//
//  AbstructComponentFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#include "AbstructComponentFactory.h"
#include "AppManager.h"

AbstructComponentFactory::AbstructComponentFactory()
{
}

AbstructComponentFactory::~AbstructComponentFactory()
{
}

bool AbstructComponentFactory::init() {
    return true;
}

Node* AbstructComponentFactory::createObject(const ValueMap& defBody, const ValueMap& uiData) {
    Node* node = Node::create();
    node->retain();
    setProperty(node, uiData);
    return node;
}

void AbstructComponentFactory::setProperty(Node* node, const ValueMap& uiData) {
    // 一般的なプロパティは_nodeに対して行う。
    if (node != NULL && !uiData.empty()) {
        // must
        float pos_x = uiData.at("pos_x").asFloat();
        float pos_y = uiData.at("pos_y").asFloat();
        float anchor_x = uiData.at("anchor_x").asFloat();
        float anchor_y = uiData.at("anchor_y").asFloat();
        
        // optional
        float scale = (uiData.find("scale") != uiData.end()) ? uiData.at("scale").asFloat() : 1.0f;
        int tag = (uiData.find("tag") != uiData.end()) ? uiData.at("tag").asInt() : -1;
        int order = (uiData.find("order") != uiData.end()) ? uiData.at("order").asInt() : -1;
        bool useRelative = (uiData.find("useRelative") != uiData.end()) ? uiData.at("useRelative").asBool() : false;
        
        Vec2 pos(pos_x, pos_y);
        if (!useRelative) {
            AppManager::getInstance()->getWorldPos(pos);
        }
        node->setPosition(pos);
        node->setAnchorPoint(Vec2(anchor_x, anchor_y));
        node->setScale(scale, scale);
        node->setTag(tag);
        node->setZOrder(order);
    }
}