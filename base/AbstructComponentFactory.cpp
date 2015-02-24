//
//  AbstructComponentFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#include "AbstructComponentFactory.h"

AbstructComponentFactory::AbstructComponentFactory()
: _node(NULL)
{
}

AbstructComponentFactory::~AbstructComponentFactory()
{
}

bool AbstructComponentFactory::init() {
    // 初期設定のまま使う。この_nodeに対してコンポーネントをぶら下げて返す。
    _node = Node::create();
    return true;
}

Node* AbstructComponentFactory::setProperty(const ValueMap& uiData) {
    // 一般的なプロパティは_nodeに対して行う。
    if (_node != NULL && !uiData.empty()) {
        // must
        float pos_x = uiData.at("pos_x").asFloat();
        float pos_y = uiData.at("pos_y").asFloat();
        float anchor_x = uiData.at("anchor_x").asFloat();
        float anchor_y = uiData.at("anchor_y").asFloat();
        
        // optional
        float scale = (uiData.find("scale") != uiData.end()) ? uiData.at("scale").asFloat() : 1.0f;
        int tag = (uiData.find("tag") != uiData.end()) ? uiData.at("tag").asInt() : -1;
        int order = (uiData.find("order") != uiData.end()) ? uiData.at("order").asInt() : -1;
        
        _node->setPosition(Vec2(pos_x, pos_y));
        _node->setAnchorPoint(Vec2(anchor_x, anchor_y));
        _node->setScale(scale, scale);
        _node->setTag(tag);
        _node->setZOrder(order);
    }
    return NULL;
}

void AbstructComponentFactory::addChild(Node* child) {
    _node->addChild(child);
}