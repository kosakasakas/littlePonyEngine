//
//  MenuItemFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/18.
//
//

#ifndef __BabylonClicker__MenuItemFactory__
#define __BabylonClicker__MenuItemFactory__

#include "cocos2d.h"
#include "AbstructComponentFactory.h"

using namespace cocos2d;

class MenuItemFactory : public AbstructComponentFactory
{
public:
    MenuItemFactory();
    virtual ~MenuItemFactory();
    CREATE_FUNC(MenuItemFactory);
    virtual Node* createObject(const ValueMap& defBody, const ValueMap& uiData);
    void createMenuItemVector(Vector<MenuItem*>& destVector, const ValueMap& defBody, const ValueMap& uiData);
    MenuItem* createMenuItem(const ValueMap& defBody, const ValueMap& uiData);
    void onButtonCalled(Ref* sender);
};

#endif /* defined(__BabylonClicker__MenuItemFactory__) */
