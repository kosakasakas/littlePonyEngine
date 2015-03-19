//
//  UIFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/20.
//
//

#include "UIFactory.h"
#include "LabelFactory.h"
#include "SpriteFactory.h"
#include "LayerFactory.h"
#include "MenuFactory.h"
#include "LittlePonyController.h"

UIFactory::UIFactory()
: _uidefMap(NULL)
{
}

UIFactory::~UIFactory()
{
    _uidefMap->release();
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
    
    // defMapはLittlePonyControlerにキャッシュされているのを基本的には使うが、ファイルパスがuidef.plist以外の場合はそっちを使う。
    if (path == "uidef.plist") {
        _uidefMap = LittlePonyController::getInstatnce()->getUIDefMap();
    } else {
        _uidefMap = UIDefMap::create(path);
    }
    _uidefMap->retain();
    
    return true;
}

Node* UIFactory::createObject(const std::string& uiType, const std::string& uiDef, const ValueMap& uiData) {
    ValueMap defBody;
    _uidefMap->copyDef(uiType, uiDef, defBody);
    
    Node* ret = createNode(uiType, defBody, uiData);
    
    return ret;
}

Node* UIFactory::createNode(const std::string& uiType, const ValueMap& defBody, const ValueMap& uiData) {
    Node* ret = NULL;
    if (uiType == UIDefMap::UI_TYPE[0]) {
        //ButtonFactory* bf = ButtonFactory::create();
        MenuFactory* bf = MenuFactory::create();
        ret = bf->createObject(defBody, uiData);
    } else if (uiType == UIDefMap::UI_TYPE[1]) {
        LabelFactory* lf = LabelFactory::create();
        ret = lf->createObject(defBody, uiData);
    } else if (uiType == UIDefMap::UI_TYPE[3]) {
        AbstructComponentFactory* acf = AbstructComponentFactory::create();
        ret = acf->createObject(defBody, uiData);
    } else if (uiType == UIDefMap::UI_TYPE[4]) {
        SpriteFactory* sf = SpriteFactory::create();
        ret = sf->createObject(defBody, uiData);
    } else if (uiType == UIDefMap::UI_TYPE[5]) {
        LayerFactory* lf = LayerFactory::create();
        ret = lf->createObject(defBody, uiData);
    } else {
        CCLOG("can not support this UI type");
    }
    return ret;
}