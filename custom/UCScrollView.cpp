//
//  UCScrollView.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#include "UCScrollView.h"
#include "UCScrollableMenu.h"

const float UCScrollView::MIN_DISTANCE = 10;

UCScrollView::UCScrollView(Menu* menu)
: CustomScrollView::CustomScrollView()
, menu(NULL)
, waitingTouchEnd(false)
{
    setMenu(menu);
}

UCScrollView* UCScrollView::create(Menu* menu) {
    UCScrollView* pRet = new UCScrollView(menu);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

UCScrollView* UCScrollView::create(Size size, Node* container, Menu* menu)
{
    UCScrollView* pRet = new UCScrollView(menu);
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}



bool UCScrollView::init() {
    if ( !CustomScrollView::init() ) {
        return false;
    }
    return true;
}

bool UCScrollView::onTouchBegan(Touch* touch, Event* event) {
    CCLOG("UCScrollView onTouchBegan called.");
    pressPoint = touch->getLocationInView();
    if (menu && !waitingTouchEnd) {
        CCLOG("onTouchBegin-onTouchbegin");
        waitingTouchEnd = menu->onTouchBegan(touch, event);
    }
    return CustomScrollView::onTouchBegan(touch, event);
}

void UCScrollView::onTouchCancelled(Touch* touch, Event* event) {
    if (menu && waitingTouchEnd) {
        CCLOG("onTouchCancelled-onTouchCancelled");
        menu->onTouchCancelled(touch, event);
        waitingTouchEnd = false;
    }
    CustomScrollView::onTouchCancelled(touch, event);
}

void UCScrollView::onTouchEnded(Touch* touch, Event* event) {
    if (menu && waitingTouchEnd) {
        Point endPoint = touch->getLocationInView();
        float distance = endPoint.getDistance(pressPoint);
        if (distance < MIN_DISTANCE) {
            CCLOG("onTouchEnded-onTouchEnded");
            menu->onTouchEnded(touch, event);
        } else {
            CCLOG("onTouchEnded-onTouchCancelled");
            menu->onTouchCancelled(touch, event);
        }
        waitingTouchEnd = false;
    }
    CustomScrollView::onTouchEnded(touch, event);
}

void UCScrollView::onTouchMoved(Touch* touch, Event* event) {
    if (menu && waitingTouchEnd) {
        Point endPoint = touch->getLocationInView();
        float distance = endPoint.getDistance(pressPoint);
        if (distance < MIN_DISTANCE) {
            CCLOG("onTouchMoved-onTouchMoved");
            menu->onTouchMoved(touch, event);
        } else {
            CCLOG("onTouchMoved-onTouchCancelled");
            menu->onTouchCancelled(touch, event);
            waitingTouchEnd = false;
        }
    }
    CustomScrollView::onTouchMoved(touch, event);
}

void UCScrollView::addTouchListener() {
    if (_touchListener != nullptr) {
        return;
    }
    auto dispatcher = EventDispatcher::getInstance();
    if( getTouchMode() == Touch::DispatchMode::ALL_AT_ONCE )
    {
        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ALL_AT_ONCE);
        
        listener->onTouchBegan = CC_CALLBACK_2(UCScrollView::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(UCScrollView::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(UCScrollView::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(UCScrollView::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithFixedPriority(listener, kUCScrollViewPriority);
        _touchListener = listener;
    }
    else
    {
        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(isSwallowsTouches());
        
        listener->onTouchBegan = CC_CALLBACK_2(UCScrollView::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(UCScrollView::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(UCScrollView::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(UCScrollView::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithFixedPriority(listener, kUCScrollViewPriority);
        _touchListener = listener;
    }
}

void UCScrollView::setMenu(Menu *menu) {
    this->menu = menu;
    UCScrollableMenu* scrollableMenu = dynamic_cast<UCScrollableMenu*>(menu);
    if(scrollableMenu) {
        scrollableMenu->setValidTouchRectInWorldSpace(getViewRect());
    }
}