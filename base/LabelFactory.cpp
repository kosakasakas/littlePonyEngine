//
//  LabelFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/23.
//
//

#include "LabelFactory.h"
#include "LittlePonyController.h"

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
    std::string colorDef = (valMap.find("colorDef") != valMap.end())
                            ? valMap.at("colorDef").asString()
                            : "";
    
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
    
    if (!colorDef.empty()) {
        Color3B color = LittlePonyController::getInstatnce()->getUIDefMap()->getColor(colorDef);
        label->setColor(color);
    }
    
    setProperty(label, uiData);
    label->retain();
    return label;
}