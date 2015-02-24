//
//  UIFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/20.
//
//

#ifndef __BabylonClicker__UIFactory__
#define __BabylonClicker__UIFactory__

#include "cocos2d.h"

using namespace cocos2d;

class UIFactory : public Ref {
public:
    static const std::string UI_TYPE[];
    UIFactory();
    virtual ~UIFactory();
    virtual bool init(const std::string& fileName);
    static UIFactory* create(const std::string& fileName);
    static UIFactory* create();
    Node* createObject(const std::string& uiType, const std::string& uiDef, const ValueMap& uiData);
private:
    ValueMap _uiDefMap;
    Node* createNode(const std::string& uiType, const ValueMap& defBody, const ValueMap& uiData);
};

#endif /* defined(__BabylonClicker__UIFactory__) */
