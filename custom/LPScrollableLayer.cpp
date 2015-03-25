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
, _originalContainerPos(0,0)
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
    
    updateScrollInfo();
    
    return true;
}

bool LPScrollableLayer::onTouchBegan(Touch* touch, Event* event) {
    CCLOG("LPScrollableLayer onTouchBegan called.");
    _pressPoint = touch->getLocationInView();
    _container->stopAllActions();
    if (_containerMenu && !_waitingTouchEnd) {
        CCLOG("onTouchBegin-onTouchbegin");
        _waitingTouchEnd = _containerMenu->onTouchBegan(touch, event);
    }
    
    // タッチ透過エリア内ならfalse
    if (_maskArea.containsPoint(_pressPoint)) {
        return false;
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

void LPScrollableLayer::setContentOffset(Vec2 offset, bool animated) {
    
    _validScrollableDistMap.clear();
    
    LPScrollView::setContentOffset(offset, animated);
    updateScrollInfo();
    _offset = offset;
    
    /*
    // Offsetを入れる前の位置を原点として持っておく
    _originalContainerPos = _container->getPosition();
    
    // Offsetを入れた後の位置から有効スクロール距離を計算しておく
    LPScrollView::setContentOffset(offset, animated);
    getScrollableDistance(_validScrollableDistMap, _container->getPosition());
    
    // Offsetを入れた後の位置を原点に入れ替える
    _originalContainerPos = _container->getPosition();
     */
}

void LPScrollableLayer::setViewSize(Size size) {
    LPScrollView::setViewSize(size);
    updateScrollInfo();
}

void LPScrollableLayer::setMaskArea(Rect& area) {
    Vec2 origin = this->convertToNodeSpace(area.origin);
    _maskArea.origin = origin;
    _maskArea.size = area.size;
}

void LPScrollableLayer::updateScrollInfo() {
    Size containerSize = _container->getContentSize();
    Size viewSize = getViewSize();
    
    // _vieawableの基点は常に原点であるという前提
    _viewableX = 0;
    _viewableY = 0;
    
    float maxX = containerSize.width - viewSize.width;
    float maxY = containerSize.height - viewSize.height;

    _scrollableX = (maxX > 0) ? maxX : 0;
    _scrollableY = (maxY > 0) ? maxY : 0;
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
    fitToAction(direction, distance * speed);
}

Vec2 makeDirVec(LPScrollableLayer::XTTouchDirection direction) {
    Vec2 delta;
    if (direction == LPScrollableLayer::RIGHT) {
        delta.x = -1;
        delta.y = 0;
    } else if (direction == LPScrollableLayer::LEFT) {
        delta.x = 1;
        delta.y = 0;
    } else if (direction == LPScrollableLayer::DOWN) {
        delta.x = 0;
        delta.y = 1;
    } else if (direction == LPScrollableLayer::UP) {
        delta.x = 0;
        delta.y = -1;
    } else {
        delta.x = 0;
        delta.y = 0;
    }
    return delta;
}

bool LPScrollableLayer::canScrollHorizontal()
{
    return getContentSize().width > getViewSize().width;
}

bool LPScrollableLayer::canScrollVertical()
{
    return getContentSize().height > getViewSize().height;
}


void LPScrollableLayer::fitToAction(XTTouchDirection direction, float distance)
{
    
    Vec2 dir = makeDirVec(direction);
    Vec2 delta = distance * dir;
    
    // Cは現時点での_containerの位置、C_dashはdelta分移動した時点での位置
    Vec2 pos = _container->getPosition();
    Vec2 C_dash(pos.x + delta.x, pos.y + delta.y);
    Vec2 C(pos.x, pos.y);
    
    // distはviewRectからC or C_dashまでの距離
    Vec2 dist(C.x - _viewableX, C.y - _viewableY);
    Vec2 dist_dash(C_dash.x - _viewableX, C_dash.y - _viewableY);
    
    // スクロール方向によりアニメーションを変える
    if (direction == LPScrollableLayer::RIGHT) {
        // TODO
    } else if (direction == LPScrollableLayer::LEFT) {
        // TODO
    } else if (direction == LPScrollableLayer::DOWN && _scrollableY > 0) {
        // スタート時点でスクロール可能範囲内にいるときのみアニメーション
        bool canScrollable = ((dist.y - _viewableY)<0);
        if (canScrollable) {
            
            // 移動後のCの位置がスクロール範囲外にいる場合は、中に収まるように移動距離を補正する
            float diff_dash = dist_dash.y - _viewableY;
            float correct_diff_dash = (diff_dash > 0) ? -diff_dash : 0;
            if (correct_diff_dash < 0) {
                C_dash = C_dash + (correct_diff_dash * dir);
            }
            
            MoveTo* moveTo = CCMoveTo::create(1.0, C_dash);
            Action* action = EaseBackOut::create(moveTo);
            _container->runAction(action);
        }
    } else if (direction == LPScrollableLayer::UP && _scrollableY > 0) {
        // スタート時点でスクロール可能範囲内にいるときのみアニメーション
        bool canScrollable = !((-dist.y - _scrollableY)>0);
        if (canScrollable) {
            
            // 移動後のCの位置がスクロール範囲外にいる場合は、中に収まるように移動距離を補正する
            float diff_dash = -dist_dash.y - _scrollableY;
            float correct_diff_dash = (diff_dash > 0) ? -diff_dash : 0;
            if (correct_diff_dash < 0) {
                C_dash = C_dash + (correct_diff_dash * dir);
            }
            
            MoveTo* moveTo = CCMoveTo::create(1.0, C_dash);
            Action* action = EaseBackOut::create(moveTo);
            _container->runAction(action);
        }
    }
}