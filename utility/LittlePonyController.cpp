//
//  PlistLoader.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/18.
//
//

#include "LittlePonyController.h"
#include "NodeFactory.h"
using namespace cocos2d;

LittlePonyController* LittlePonyController::_singleton = NULL;

LittlePonyController::LittlePonyController()
: _uiDefMap(NULL)
{
}

LittlePonyController::~LittlePonyController()
{
}

LittlePonyController* LittlePonyController::getInstatnce() {
    if( NULL == _singleton) {
        _singleton = new LittlePonyController();
        _singleton->init();
    }
    return _singleton;
}

bool LittlePonyController::init() {
    _uiDefMap = UIDefMap::create();
    return true;
}

Ref* LittlePonyController::getData(const char* fileName, const char* tagName) {
    Ref* res;
    std::string path = FileUtils::getInstance()->fullPathForFilename(fileName);
    if (path.empty())
    {
        return NULL;
    }
    ValueMap allData = FileUtils::getInstance()->getValueMapFromFile(path);
    ValueMap targetData = allData.at(tagName).asValueMap();
    std::string tag = targetData.at("type").asString();
    if (tag == "node") {
        const ValueMap body = targetData.at("body").asValueMap();
        NodeFactory* nf = NodeFactory::create();
        Node* node = nf->createObject(body);
        return node;
    } else if (tag == "uidef") {
        return NULL;
    } else {
        res = NULL;
    }
    return res;
}
