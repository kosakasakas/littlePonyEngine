//
//  LabelFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/23.
//
//

#include "LabelFactory.h"

LabelFactory::LabelFactory()
{
}

LabelFactory::~LabelFactory()
{
}

Node* LabelFactory::createObject(const ValueMap& valMap, const ValueMap& uiData) {
    // from defMap
    std::string font = valMap.at("font").asString();
    std::string fontType = valMap.at("fontType").asString();
    int size = valMap.at("size").asInt();
    
    // from uiData
    std::string text = uiData.at("text").asString();
    
    Label* label;
    if (fontType == "system") {
        label = Label::createWithSystemFont(text, font, size);
    } else if (fontType == "ttf") {
        label = Label::createWithTTF(text, font, size);
    } else if (fontType == "bmfont") {
        label = Label::createWithBMFont(font, text);
    }
    
    addChild(label);
    setProperty(uiData);
    
    return getNode();
}