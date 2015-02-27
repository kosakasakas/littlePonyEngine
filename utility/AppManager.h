//
//  AppManager.h
//  UCEngine
//
//  Created by 小坂 昂大 on 2014/07/12.
//
//

#ifndef __UCEngine__AppManager__
#define __UCEngine__AppManager__

#include <iostream>
#include "cocos2d.h"
#include "AppMacros.h"

class AppManager
{
private:
    static AppManager* _singleton;
    
    AppManager();
    virtual ~AppManager();
    void init();
    static Resource getRunningDeviceResource();
    void setAssetResolution();
    
public:
    static AppManager* getInstance();
    CC_SYNTHESIZE_READONLY(DeviceType, _runningDeviceType, RunningDeviceType);
    CC_SYNTHESIZE_READONLY(Resource*, _resource, Resource);
    
    enum WORLD_ANCHOR_TYPE {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };
    CC_SYNTHESIZE(WORLD_ANCHOR_TYPE, _worldAnchor, WorldAnchor);
    void getWorldPos(cocos2d::Vec2& pos);
};

#endif /* defined(__UCEngine__AppManager__) */
