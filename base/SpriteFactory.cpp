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
    // from uiData
    std::string image = uiData.at("image").asString();
    
    // spriteの場合は、rootNodeにぶら下げると無駄にnodeが増えるだけなので、直接sriteにパラメータ付けて返す
    //Node* node = AbstructComponentFactory::createObject(valMap, uiData);
    //node->retain();
    
    Sprite* sp = Sprite::create(image);
    sp->retain();
    setProperty(sp, uiData);
    
    //node->addChild(sp);
    
    return sp;
}