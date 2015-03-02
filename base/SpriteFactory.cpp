//
//  SpriteFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/02.
//
//

#include "SpriteFactory.h"
#include "LittlePonyController.h"

SpriteFactory::SpriteFactory()
{
}

SpriteFactory::~SpriteFactory()
{
}

Node* SpriteFactory::createObject(const ValueMap& valMap, const ValueMap& uiData) {
    Node* node = AbstructComponentFactory::createObject(valMap, uiData);
    node->retain();
    
    // from uiData
    std::string image = uiData.at("image").asString();
    
    Sprite* sp = Sprite::create(image);
    
    node->addChild(sp);
    
    return node;
}