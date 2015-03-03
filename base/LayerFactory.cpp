//
//  LayerFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/03.
//
//

#include "LayerFactory.h"
#include "LittlePonyController.h"

LayerFactory::LayerFactory()
{
}

LayerFactory::~LayerFactory()
{
}

Node* LayerFactory::createObject(const ValueMap& valMap, const ValueMap& uiData) {
    // from uiData
    int width = uiData.at("size_width").asInt();
    int height = uiData.at("size_height").asInt();
    std::string colorDef = (uiData.find("colorDef") != uiData.end())
    ? uiData.at("colorDef").asString()
    : "";
    
    Layer* layer;
    
    if (!colorDef.empty()) {
        Color3B color = LittlePonyController::getInstatnce()->getUIDefMap()->getColor(colorDef);
        layer = LayerColor::create(Color4B(color.r, color.g, color.b,255), width, height);
    }
    
    layer->retain();
    setProperty(layer, uiData);
    
    return layer;
}
