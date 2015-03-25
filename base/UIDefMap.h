//
//  UIDefMap.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#ifndef __BabylonClicker__UIDefMap__
#define __BabylonClicker__UIDefMap__

#include "cocos2d.h"

using namespace cocos2d;

class UIDefMap : public Ref {
public:
    UIDefMap();
    virtual ~UIDefMap();
    
    virtual bool init(const std::string& fileName);
    
    static UIDefMap* create(const std::string& fileName);
    static UIDefMap* create();
    
    static const std::string UI_TYPE_NAME[];
    enum UI_TYPE {
        BUTTON,
        LABEL,
        COLOR,
        NODE,
        SPRITE,
        LAYER,
        NUM
    };
    
    void copyDef(const std::string& uiType, const std::string& uiDef, ValueMap& targetMap);
    const Color3B getColor(const std::string& colorDef);
    
private:
    ValueMap _uiDefMap;
};


#endif /* defined(__BabylonClicker__UIDefMap__) */
