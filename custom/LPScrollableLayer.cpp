//
//  LPScrollableLayer.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/11.
//
//

#include "LPScrollableLayer.h"
#include "LPScrollableMenu.h"

const float LPScrollableLayer::MIN_DISTANCE = 10;

LPScrollableLayer::LPScrollableLayer()
: LPScrollView::LPScrollView()
, _waitingTouchEnd(false)
, _containerMenu(NULL)
{
}

LPScrollableLayer::LPScrollableLayer(Layer* containerMenu)
: LPScrollView::LPScrollView()
, _waitingTouchEnd(false)
{
    _containerMenu = containerMenu;
}

LPScrollableLayer::~LPScrollableLayer()
{
    if (_containerMenu != NULL) {
        _containerMenu->release();
    }
}

LPScrollableLayer* LPScrollableLayer::create(Layer* containerMenu) {
    Size size(0,0);
    return create(size, containerMenu);
}

LPScrollableLayer* LPScrollableLayer::create(Size size, Layer* containerMenu)
{
    LPScrollableLayer* pRet = new LPScrollableLayer(containerMenu);
    if (pRet && pRet->initWithViewSize(size, NULL))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool LPScrollableLayer::init() {
    if ( !LPScrollView::init() ) {
        return false;
    }
    return true;
}

bool LPScrollableLayer::onTouchBegan(Touch* touch, Event* event) {
    CCLOG("LPScrollableLayer onTouchBegan called.");
    _pressPoint = touch->getLocationInView();
    if (_containerMenu && !_waitingTouchEnd) {
        CCLOG("onTouchBegin-onTouchbegin");
        _waitingTouchEnd = _containerMenu->onTouchBegan(touch, event);
    }
    return LPScrollView::onTouchBegan(touch, event);
}

void LPScrollableLayer::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
}

void LPScrollableLayer::onTouchCancelled(Touch* touch, Event* event) {
    if (_containerMenu && _waitingTouchEnd) {
        CCLOG("onTouchCancelled-onTouchCancelled");
        _containerMenu->onTouchCancelled(touch, event);
        _waitingTouchEnd = false;
    }
    LPScrollView::onTouchCancelled(touch, event);
}

void LPScrollableLayer::onTouchesCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
}

void LPScrollableLayer::onTouchEnded(Touch* touch, Event* event) {
    if (_containerMenu && _waitingTouchEnd) {
        Point endPoint = touch->getLocationInView();
        float distance = endPoint.getDistance(_pressPoint);
        if (distance < MIN_DISTANCE) {
            CCLOG("onTouchEnded-onTouchEnded");
            _containerMenu->onTouchEnded(touch, event);
        } else {
            CCLOG("onTouchEnded-onTouchCancelled");
            _containerMenu->onTouchCancelled(touch, event);
        }
        _waitingTouchEnd = false;
    }
    LPScrollView::onTouchEnded(touch, event);
}

void LPScrollableLayer::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
}

void LPScrollableLayer::onTouchMoved(Touch* touch, Event* event) {
    if (_containerMenu && _waitingTouchEnd) {
        Point endPoint = touch->getLocationInView();
        float distance = endPoint.getDistance(_pressPoint);
        if (distance < MIN_DISTANCE) {
            CCLOG("onTouchMoved-onTouchMoved");
            _containerMenu->onTouchMoved(touch, event);
        } else {
            CCLOG("onTouchMoved-onTouchCancelled");
            _containerMenu->onTouchCancelled(touch, event);
            _waitingTouchEnd = false;
        }
    }
    LPScrollView::onTouchMoved(touch, event);
}

void LPScrollableLayer::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
}

void LPScrollableLayer::addTouchListener() {
    if (_touchListener != nullptr) {
        return;
    }
    auto dispatcher = getEventDispatcher();
    if( getTouchMode() == Touch::DispatchMode::ALL_AT_ONCE )
    {
        /*// Register Touch Event
        auto listener = EventListenerTouchAllAtOnce::create();
        
        listener->onTouchesBegan = CC_CALLBACK_2(LPScrollableLayer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(LPScrollableLayer::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(LPScrollableLayer::onTouchesEnded, this);
        listener->onTouchesCancelled = CC_CALLBACK_2(LPScrollableLayer::onTouchesCancelled, this);
        
        dispatcher->addEventListenerWithFixedPriority(listener, kLPScrollableLayerPriority);
        _touchListener = listener;*/
    }
    else
    {
        // Register Touch Event
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(isSwallowsTouches());
        
        listener->onTouchBegan = CC_CALLBACK_2(LPScrollableLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(LPScrollableLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(LPScrollableLayer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(LPScrollableLayer::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithFixedPriority(listener, kLPScrollableLayerPriority);
        _touchListener = listener;
    }
}

void LPScrollableLayer::onEnter() {
    LPScrollView::onEnter();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(isSwallowsTouches());
    
    listener->onTouchBegan = CC_CALLBACK_2(LPScrollableLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LPScrollableLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LPScrollableLayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(LPScrollableLayer::onTouchCancelled, this);
    
    // スクロールレイヤーより先にボタンがタッチを取らせないようにする。
    dispatcher->addEventListenerWithFixedPriority(listener, kLPScrollableLayerPriority);
    _touchListener = listener;
}

void LPScrollableLayer::onExit() {
    LPScrollView::onExit();
}

void LPScrollableLayer::setLPContainer(Layer *menu) {
    _containerMenu = menu;
    _containerMenu->retain();
    LPScrollableMenu* scrollableMenu = dynamic_cast<LPScrollableMenu*>(menu);
    if(scrollableMenu) {
        scrollableMenu->setValidTouchRectInWorldSpace(getViewRect());
    }
    this->addChild(menu);
}

void LPScrollableLayer::xtTapGesture(Point position) {
    CCLOG("xtTap");
}

void LPScrollableLayer::xtDoubleTapGesture(Point position) {
    CCLOG("xtDoubleTap");
}

void LPScrollableLayer::xtLongTapGesture(Point position) {
    CCLOG("xtLongTap");
}

void LPScrollableLayer::xtSwipeGesture(XTTouchDirection direction, float distance, float speed) {
    CCLOG("xtSwipe");
}