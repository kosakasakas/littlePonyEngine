//
//  MenuFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/18.
//
//

#ifndef __BabylonClicker__MenuFactory__
#define __BabylonClicker__MenuFactory__

#include "cocos2d.h"
#include "AbstructComponentFactory.h"

using namespace cocos2d;

class MenuFactory : public AbstructComponentFactory
{
public:
    MenuFactory();
    virtual ~MenuFactory();
    CREATE_FUNC(MenuFactory);
    virtual Node* createObject(const ValueMap& defBody, const ValueMap& uiData);
    void onButtonCalled(Ref* sender);
};


#endif /* defined(__BabylonClicker__MenuFactory__) */
