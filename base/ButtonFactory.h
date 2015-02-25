//
//  ButtonFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/23.
//
//

#ifndef __BabylonClicker__ButtonFactory__
#define __BabylonClicker__ButtonFactory__

#include "cocos2d.h"
#include "AbstructComponentFactory.h"

using namespace cocos2d;

class ButtonFactory : public AbstructComponentFactory
{
public:
    ButtonFactory();
    virtual ~ButtonFactory();
    CREATE_FUNC(ButtonFactory);
    virtual Node* createObject(const ValueMap& defBody, const ValueMap& uiData);
    void onButtonCalled(Ref* sender);
};

#endif /* defined(__BabylonClicker__ButtonFactory__) */
