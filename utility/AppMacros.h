//
//  AppMacros.h
//  UCEngine
//
//  Created by Takahiro Kosaka on 2014/04/14.
//
//

#ifndef UCEngine_AppMacros_h
#define UCEngine_AppMacros_h

#include "cocos2d.h"

typedef struct tagResource {
    cocos2d::Size size;  // 論理解像度
    char directory[100]; // 優先検索するリソースディレクトリ
    float scaleFactor;   // コンテンツのスケール倍率
    ResolutionPolicy policy; // フィットポリシー
} Resource;

static Resource small_16x9 = {cocos2d::Size(320, 568), "resources-small", 1.0, ResolutionPolicy::FIXED_WIDTH};
static Resource small_3x2  = {cocos2d::Size(320, 480), "resources-small", 1.0, ResolutionPolicy::FIXED_WIDTH};
static Resource small_4x3  = {cocos2d::Size(320, 480), "resources-small", 1.0, ResolutionPolicy::FIXED_HEIGHT};

static Resource medium_16x9 = {cocos2d::Size(320, 568), "resources-medium", 1.5, ResolutionPolicy::FIXED_WIDTH};
static Resource medium_3x2  = {cocos2d::Size(320, 480), "resources-medium", 1.5, ResolutionPolicy::FIXED_WIDTH};
static Resource medium_4x3  = {cocos2d::Size(320, 480), "resources-medium", 1.5, ResolutionPolicy::FIXED_HEIGHT};

static Resource large_16x9 = {cocos2d::Size(320, 568), "resources-large", 2.0, ResolutionPolicy::FIXED_WIDTH};
static Resource large_3x2  = {cocos2d::Size(320, 480), "resources-large", 2.0, ResolutionPolicy::FIXED_WIDTH};
static Resource large_4x3  = {cocos2d::Size(320, 480), "resources-large", 2.0, ResolutionPolicy::FIXED_HEIGHT};

static Resource xlarge_16x9 = {cocos2d::Size(320, 568), "resources-xlarge", 4.0, ResolutionPolicy::FIXED_WIDTH};
static Resource xlarge_3x2  = {cocos2d::Size(320, 480), "resources-xlarge", 4.0, ResolutionPolicy::FIXED_WIDTH};
static Resource xlarge_4x3  = {cocos2d::Size(320, 480), "resources-xlarge", 4.0, ResolutionPolicy::FIXED_HEIGHT};

enum DeviceType {
    DeviceType_iPhone4,
    DeviceType_iPhone5,
    DeviceType_iPad,
    DeviceType_iPadRetina,
    DeviceType_Android,
    DeviceType_AndroidTablet,
    DeviceType_NUM
};

#endif
