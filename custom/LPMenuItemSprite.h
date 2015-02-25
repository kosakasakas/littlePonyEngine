//
//  LPMenuItemSprite.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#ifndef __BabylonClicker__LPMenuItemSprite__
#define __BabylonClicker__LPMenuItemSprite__

#include "cocos2d.h"

using namespace cocos2d;

class LPMenuItemSprite : public MenuItemSprite
{
public:
    LPMenuItemSprite();
    virtual ~LPMenuItemSprite();
    static LPMenuItemSprite* create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback, Node* targetNode);
    static LPMenuItemSprite* create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback, Node* targetNode);
    virtual void onEnter();
    virtual void onExit();
    virtual void selected();
    virtual void unselected();
    virtual void activate();
protected:
    float _oldScaleX, _oldScaleY;
    Node* _targetNode;
};

#endif /* defined(__BabylonClicker__LPMenuItemSprite__) */
