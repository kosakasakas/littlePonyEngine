//
//  UIFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/20.
//
//

#include "UIFactory.h"

const std::string UIFactory::UI_TYPE[] = {"button","label"};

UIFactory::UIFactory()
{
}

UIFactory::~UIFactory()
{
}

static UIFactory* create(std::string fileName)
{
    UIFactory *pRet = new UIFactory();
    if (pRet && pRet->init(fileName))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool UIFactory::init(std::string fileName) {
    std::string path = FileUtils::getInstance()->fullPathForFilename(fileName);
    if (path.empty())
    {
        return false;
    }
    ValueVector vec = FileUtils::getInstance()->getValueVectorFromFile(path);
    for (Value val : vec) {
        ValueMap data = val.asValueMap();
        std::string type = data.at("type").asString();
        if (type == "uidef") {
            ValueMap body = data.at("body").asValueMap();
            ValueVector children = body.at("children").asValueVector();
            for (Value child : children) {
                ValueMap def = child.asValueMap();
                std::string defType = def.at("type").asString();
                int num = sizeof(UI_TYPE)/sizeof(UI_TYPE[0]);
                for (int i = 0; i < num; ++i) {
                    if (defType == UI_TYPE[i]) {
                        _uiDefMap.insert(UI_TYPE[i], def);
                    }
                }
            }
        }
    }
    return true;
}

Node* UIFactory::createObject(std::string tag, std::string def) {
    ValueMap defMap = _uiDefMap.at(tag);
    
    
}