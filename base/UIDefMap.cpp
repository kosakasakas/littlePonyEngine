//
//  UIDefMap.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#include "UIDefMap.h"

const std::string UIDefMap::UI_TYPE_NAME[] = {"button","label","color", "node", "sprite", "layer"};

UIDefMap::UIDefMap()
{
}

UIDefMap::~UIDefMap()
{
}

UIDefMap* UIDefMap::create(const std::string& fileName)
{
    UIDefMap *pRet = new UIDefMap();
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

// デフォルトではuidef.plistから定義一覧を取得する。
UIDefMap* UIDefMap::create() {
    const std::string fileName = "uidef.plist";
    return create(fileName);
}

bool UIDefMap::init(const std::string& fileName) {
    std::string path = FileUtils::getInstance()->fullPathForFilename(fileName);
    if (path.empty())
    {
        return false;
    }
    
    ValueMap map = FileUtils::getInstance()->getValueMapFromFile(path);
    for (ValueMap::iterator it = map.begin(); it != map.end(); ++it) {
        std::string id = it->first;
        Value val = it->second;
        ValueMap data = val.asValueMap();
        std::string type = data.at("type").asString();
        if (type == "uidef") {
            ValueMap body = data.at("body").asValueMap();
            ValueVector children = body.at("children").asValueVector();
            for (Value child : children) {
                ValueMap def = child.asValueMap();
                std::string defType = def.at("type").asString();
                
                for (int i = 0; i < UI_TYPE::NUM; ++i) {
                    if (defType == UI_TYPE_NAME[i]) {
                        if (_uiDefMap.find(defType) == _uiDefMap.end()) {
                            // not found
                            ValueVector vec;
                            vec.push_back(child);
                            _uiDefMap[defType] = vec;
                        } else {
                            // fond
                            ValueVector vec = _uiDefMap[defType].asValueVector();
                            vec.push_back(child);
                            _uiDefMap[defType] = vec;
                        }
                    }
                }
            }
        } else {
            CCLOG("can not recognize %s.", type.c_str());
        }
        
    }
    return true;
}

void UIDefMap::copyDef(const std::string& uiType, const std::string& uiDef, ValueMap& targetMap) {
    if (_uiDefMap.find(uiType) == _uiDefMap.end()) {
        CCLOG("can not recognize UI type: %s", uiType.c_str());
        return;
    }
    ValueVector defVec = _uiDefMap.at(uiType).asValueVector();
    for (Value def : defVec) {
        ValueMap defBody = def.asValueMap();
        std::string name = defBody.at("name").asString();
        if (name == uiDef) {
            targetMap = defBody;
        } else {
            CCLOG("can not find UI def: %s", uiDef.c_str());
        }
    }
}

const Color3B UIDefMap::getColor(const std::string& colorDef) {
    Color3B color;
    ValueVector colorVec = _uiDefMap.at(UI_TYPE_NAME[UI_TYPE::COLOR]).asValueVector();
    for (Value colorVal: colorVec) {
        ValueMap colorMap = colorVal.asValueMap();
        if (colorMap.at("name").asString() == colorDef) {
            color.r = colorMap.at("r").asInt();
            color.g = colorMap.at("g").asInt();
            color.b = colorMap.at("b").asInt();
        }
    }
    return color;
}