//
//  ObjectFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/18.
//
//

#ifndef __BabylonClicker__PlistLoader__
#define __BabylonClicker__PlistLoader__

#include "cocos2d.h"
#include "UIDefMap.h"
#include "Subject.h"
#include "LPLayer.h"

class LittlePonyController : public Ref
{
public:
    LittlePonyController();
    virtual ~LittlePonyController();
    static LittlePonyController* getInstatnce();
    bool init();
    
    // assets loader
    CC_SYNTHESIZE_READONLY(UIDefMap*, _uiDefMap, UIDefMap);
    cocos2d::Ref* getData(const char* fileName, const char* tagName);
    
    // ui notification
    void notifyUINotificationCenter(Ref* sender);
    void addToUINotificationCenter(Observer* o);
    void removeFromUINotificationCenter(Observer* o);
    
    // for cocos2d-x custom API
    void setCurrentSceneLayer(LPLayer* layer);
    void replaceScene(Scene* scene);
    
private:
    static LittlePonyController* _singleton;
    Subject* _uiNotificationCenter;
    LPLayer* _currentSceneLayer;
};


#endif /* defined(__BabylonClicker__PlistLoader__) */
