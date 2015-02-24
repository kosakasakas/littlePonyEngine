//
//  UIFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/20.
//
//

#include "UIFactory.h"
#include "ButtonFactory.h"
#include "LabelFactory.h"

const std::string UIFactory::UI_TYPE[] = {"button","label"};

UIFactory::UIFactory()
{
}

UIFactory::~UIFactory()
{
}

UIFactory* UIFactory::create(const std::string& fileName)
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

// デフォルトではuidef.plistから定義一覧を取得する。
UIFactory* UIFactory::create() {
    const std::string fileName = "uidef.plist";
    return create(fileName);
}

bool UIFactory::init(const std::string& fileName) {
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
                int num = sizeof(UI_TYPE)/sizeof(UI_TYPE[0]);
                for (int i = 0; i < num; ++i) {
                    if (defType == UI_TYPE[i]) {
                        if (_uiDefMap.find(defType) == _uiDefMap.end()) {
                            // not found
                            ValueVector vec;
                            vec.push_back(child);
                            _uiDefMap[defType] = vec;
                        } else {
                            // fond
                            ValueVector vec = _uiDefMap[defType].asValueVector();
                            vec.push_back(child);
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

Node* UIFactory::createObject(const std::string& uiType, const std::string& uiDef, const ValueMap& uiData) {
    if (_uiDefMap.find(uiType) == _uiDefMap.end()) {
         CCLOG("can not recognize this UI type.");
        return NULL;
    }
    Node* ret;
    ValueVector defVec = _uiDefMap.at(uiType).asValueVector();

    for (Value def : defVec) {
        ValueMap defBody = def.asValueMap();
        std::string name = defBody.at("name").asString();
        if (name == uiDef) {
            ret = createNode(uiType, defBody, uiData);
        } else {
            CCLOG("can not find ui name");
        }
    }
    return ret;
}

Node* UIFactory::createNode(const std::string& uiType, const ValueMap& defBody, const ValueMap& uiData) {
    Node* ret = NULL;
    if (uiType == UI_TYPE[0]) {
        ButtonFactory* bf = ButtonFactory::create();
        ret = bf->createObject(defBody, uiData);
    } else if (uiType == UI_TYPE[1]) {
        LabelFactory* lf = LabelFactory::create();
        ret = lf->createObject(defBody, uiData);
    } else {
        CCLOG("can not support this UI type");
    }
    return ret;
}