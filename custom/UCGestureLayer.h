//
//  UCGestureLayer.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/10.
//
//

#ifndef __BabylonClicker__UCGestureLayer__
#define __BabylonClicker__UCGestureLayer__

#include "XTLayer.h"

class UCGestureLayer : public XTLayer {
public:
    UCGestureLayer();
    ~UCGestureLayer();
    virtual void xtTapGesture(CCPoint position) {}
    virtual void xtDoubleTapGesture(CCPoint position) {}
    virtual void xtLongTapGesture(CCPoint position) {}
    virtual void xtSwipeGesture(XTTouchDirection direction, float distance, float speed) {}
};

#endif /* defined(__BabylonClicker__UCGestureLayer__) */
