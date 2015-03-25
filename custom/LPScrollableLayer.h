//
//  LPScrollableLayer.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/11.
//
//

#ifndef __BabylonClicker__LPScrollableLayer__
#define __BabylonClicker__LPScrollableLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "LPScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LPScrollableLayer : public LPScrollView {
public:
    LPScrollableLayer();
    LPScrollableLayer(Layer* containerMenu);
    virtual ~LPScrollableLayer();
    
    static LPScrollableLayer* create(Layer* containerMenu);
    static LPScrollableLayer* create(Size size, Layer* containerMenu = NULL);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void setContentOffset(Vec2 offset, bool animated = false);
    virtual void setViewSize(Size size);
    
    enum {
        // Menu系は-128なので、それと同等の優先度にする。
        // 一方、LPScrollableMenuについては先にタッチされると困るので、kLPScrollableLayerPriorityよりもさらに下げる。
        kLPScrollableLayerPriority = -128
    };
    
    // 実際にはsddChildさせずに_containerMenuに入れる
    virtual void setLPContainer(Layer* container);
    void setMaskArea(Rect& maskArea);
    
    // XT Gesture
    virtual void xtTapGesture(Point position);
    virtual void xtDoubleTapGesture(Point position);
    virtual void xtLongTapGesture(Point position);
    virtual void xtSwipeGesture(XTTouchDirection direction, float distance, float speed);
    
private:
    virtual bool init();
    virtual void addTouchListener();
    static const float MIN_DISTANCE;
    
    Point _pressPoint;
    Layer* _containerMenu;
    bool _waitingTouchEnd;
    Vec2 _originalContainerPos;
    ValueMap _validScrollableDistMap;
    Vec2 _offset;
    Rect _maskArea;
    
    float _viewableX;
    float _viewableY;
    float _scrollableX;
    float _scrollableY;
    
    bool canScrollHorizontal();
    bool canScrollVertical();
    void updateScrollInfo();
    
    void fitToAction(XTTouchDirection direction, float distance);
};



#endif /* defined(__BabylonClicker__LPScrollableLayer__) */
