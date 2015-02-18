//
//  TouchController.cpp
//  quadro
//
//  Created by EAA van Poeijer on 12-02-13.
//
//

#include "XTLayer.h"

XTLayer::XTLayer()
{
    this->_xtSwipeThreshold = 20;
    this->_xtSwipeTime = 500;
    this->_xtTapThreshold =10;
    this->_xtTapTime = 250;
    this->_xtLongTapTreshold = 10;
    this->_xtLongTapTime = 2000;
    this->_xtDoubleTapTime = 250;
    this->_xtNumberOfTaps = 0;
}

XTLayer::~XTLayer()
{
    
}

long XTLayer::millisecondNow()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

// Override of touches
bool XTLayer::onTouchBegan(cocos2d::Touch* _touches, cocos2d::Event* event)
{
    this->_touchHasMoved = false;
    this->_xtTouchStart = this->millisecondNow();
    //Array *allTouches = xtAllTouchextromSet(_touches);
    
    //Touch* fingerOne = (Touch *)allTouches->getObjectAtIndex(0);
    Touch* fingerOne = _touches;
    Point  pointOne = Director::getInstance()->convertToUI(fingerOne->getLocationInView());
    
    Point location = this->convertToNodeSpace(pointOne);
    this->xtGestureStartPoint= location;//touch locationInView:touch->view);
    this->xtPreviousPoint = location;
   
    // Passthrough
    this->xtTouchBegan(location);
    this->xtTouchBegan(_touches, event);
    
    return true;
}

void XTLayer::onTouchMoved(cocos2d::Touch* _touches, cocos2d::Event* event)
{
    this->_touchHasMoved = true;
    //Array *allTouches = xtAllTouchextromSet(_touches);
    
    //Touch* fingerOne = (Touch *)allTouches->getObjectAtIndex(0);
    Touch* fingerOne = _touches;
    Point pointOne = Director::getInstance()->convertToUI(fingerOne->getLocationInView());
    
    Point location = this->convertToNodeSpace(pointOne);
    this->xtActualPoint = location;
    
    CCLOG("Position:%f,%f",location.x,location.y);
    // Passthrough
    this->xtTouchMoved(location);
    this->xtTouchMoved(_touches, event);

}

void XTLayer::onTouchEnded(cocos2d::Touch* _touches, cocos2d::Event* event)
{
    long endTime = this->millisecondNow();
    long deltaTime = endTime - this->_xtTouchStart;
    CCLOG("Deltatime %ld",deltaTime);
    //Array *allTouches = xtAllTouchextromSet(_touches);
    
    //Touch* fingerOne = (Touch *)allTouches->getObjectAtIndex(0);
    Touch* fingerOne = _touches;
    Point pointOne = Director::getInstance()->convertToUI(fingerOne->getLocationInView());
    
    Point location = this->convertToNodeSpace(pointOne);
    this->xtGestureEndPoint= location;//touch locationInView:touch->view);

    // Calculate the distance
    float deltaX = this->xtGestureStartPoint.x - this->xtGestureEndPoint.x;
    float deltaY = this->xtGestureStartPoint.y - this->xtGestureEndPoint.y;
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    float horSwipeDistancePercentage = fabs((deltaX / screenSize.width) * 100);
    float verSwipeDistancePercentage = fabs((deltaY / screenSize.height) * 100);
    
    // Calculate the direction
    // First horizontal or vertical
    if (fabs(deltaX) > fabs(deltaY) && horSwipeDistancePercentage > this->_xtSwipeThreshold && deltaTime < this->_xtSwipeTime) // horizontal
    {
        if (deltaX < 0)
            this->_xtTouchDirection = LEFT;
        if (deltaX > 0)
            this->_xtTouchDirection = RIGHT;
        float speed = fabs(deltaX) / deltaTime;
        this->xtSwipeGesture(this->_xtTouchDirection, fabs(deltaX), speed);
    }
    else if (fabs(deltaX) < fabs(deltaY) && verSwipeDistancePercentage > this->_xtSwipeThreshold && deltaTime <this->_xtSwipeTime)// Vertical
    {
        if (deltaY < 0)
            this->_xtTouchDirection = DOWN;
        if (deltaY > 0)
            this->_xtTouchDirection = UP;
        float speed = fabs(deltaY) / deltaTime;
        this->xtSwipeGesture(this->_xtTouchDirection, fabs(deltaY), speed);
    }
    else if (deltaTime >= this->_xtLongTapTime)// No movement, tap detected
    {
        this->xtLongTapGesture(location);
    }
    else
        {
            if (this->_xtNumberOfTaps == 0)
            {
                this->_xtTouchStart = this->millisecondNow();
                this->schedule(schedule_selector(XTLayer::tapHandler), (this->_xtDoubleTapTime / 1000), 1, 0);
            }
            this->_xtNumberOfTaps++;
    }

    this->xtTouchEnded(location);
    this->xtTouchEnded(_touches, event);
}

Array* XTLayer::xtAllTouchextromSet(Set *_touches)
{
    Array *arr = Array::create();
    
    SetIterator it;
    
	for( it = _touches->begin(); it != _touches->end(); it++)
    {
        arr->addObject((Touch *)*it);
    }
    return arr;
    
}

void XTLayer::tapHandler(float delta)
{
    this->unschedule(schedule_selector(XTLayer::tapHandler));

    if (this->_xtNumberOfTaps == 1 && !this->_touchHasMoved) // singletap
    {
        this->_xtNumberOfTaps = 0;
        this->xtTapGesture(this->xtGestureEndPoint);
    }
    else if (this->_xtNumberOfTaps == 2) // double tap
    {
        this->_xtNumberOfTaps = 0;
        this->xtDoubleTapGesture(this->xtGestureEndPoint);
    }
    else
    {
        this->_xtNumberOfTaps = 0;
    }
}
