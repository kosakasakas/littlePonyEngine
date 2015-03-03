//
//  LPLayer.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/03.
//
//

#include "LPLayer.h"
#include "LittlePonyController.h"

void LPLayer::onEnter() {
    Layer::onEnter();
    // UI notificationを受けれるように登録しておく
    LittlePonyController::getInstatnce()->addToUINotificationCenter(this);
}

void LPLayer::onExit() {
    // NotificationCenterからremoveする。
    LittlePonyController::getInstatnce()->removeFromUINotificationCenter(this);
    Layer::onExit();
}

void LPLayer::onNotice() {
    // 必須ではないので実装はしておく
}