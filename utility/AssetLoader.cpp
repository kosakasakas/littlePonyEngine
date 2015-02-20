//
//  PlistLoader.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/18.
//
//

#include "AssetLoader.h"
#include "NodeFactory.h"
using namespace cocos2d;

AssetLoader* AssetLoader::_singleton = NULL;

AssetLoader::AssetLoader()
{
}

AssetLoader::~AssetLoader()
{
}

AssetLoader* AssetLoader::getInstatnce() {
    if( NULL == _singleton) {
        _singleton = new AssetLoader();
    }
    return _singleton;
}

Ref* AssetLoader::create(const char* fileName, const char* tagName) {
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
        ValueMap body = targetData.at("body").asValueMap();
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
