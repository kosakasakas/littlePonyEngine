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
    virtual bool init(std::string fileName);
    static UIFactory* create();
    Node* createObject(std::string tag, std::string def);
private:
    Map<std::string, ValueMap> _uiDefMap;
};

#endif /* defined(__BabylonClicker__UIFactory__) */
