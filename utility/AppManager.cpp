//
//  AppManager.cpp
//  UCEngine
//
//  Created by 小坂 昂大 on 2014/07/12.
//
//

#include "AppManager.h"

USING_NS_CC;

AppManager* AppManager::_singleton = NULL;

AppManager::AppManager()
: _resource(NULL)
, _runningDeviceType(DeviceType_Android)
{
}

AppManager::~AppManager()
{
    delete _resource;
    _resource = NULL;
}

AppManager* AppManager::getInstance() {
    if( NULL == _singleton )
    {
        _singleton = new AppManager();
        _singleton->init();
    }
    return _singleton;
}

void AppManager::init() {
    setAssetResolution();
}

void AppManager::setAssetResolution() {
    if (_resource != NULL) {
        return;
    }
    
    const Size winSize = Director::getInstance()->getWinSize();
    _resource = &small_4x3;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    float ratio = (float)winSize.height / (float)winSize.width;
    float ratio_16x9 = 16.f/9.f;
    float ratio_3x2 = 3.f/2.f;
    if (winSize.width < 540) {
        if(ratio < ratio_3x2) {
            _resource = &small_4x3;
        } else if(ratio < ratio_16x9){
            _resource = &small_3x2;
        } else {
            _resource = &small_16x9;
        }
    } else if (winSize.width < 720) {
        if(ratio < ratio_3x2) {
            _resource = &medium_4x3;
        } else if(ratio < ratio_16x9){
            _resource = &medium_3x2;
        } else {
            _resource = &medium_16x9;
        }
    } else if (winSize.width < 1080) {
        if(ratio < ratio_3x2) {
            _resource = &large_4x3;
        } else if(ratio < ratio_16x9){
            _resource = &large_3x2;
        } else {
            _resource = &large_16x9;
        }
    } else {
        if(ratio < ratio_3x2) {
            _resource = &xlarge_4x3;
        } else if(ratio < ratio_16x9){
            _resource = &xlarge_3x2;
        } else {
            _resource = &xlarge_16x9;
        }
        _runningDeviceType = DeviceType_AndroidTablet;
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (winSize.width == 320) {
        _resource = &medium_3x2;
        _runningDeviceType = DeviceType_iPhone4;
    } else if (winSize.width == 640) {
        _resource = &large_16x9;
        _runningDeviceType = DeviceType_iPhone5;
    } else if (winSize.width == 768) {
        _resource = &large_4x3;
        _runningDeviceType = DeviceType_iPad;
    } else if (winSize.width == 1536) {
        _resource = &xlarge_4x3;
        _runningDeviceType = DeviceType_iPadRetina;
    }
#endif
}