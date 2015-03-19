//
//  LayerFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/03.
//
//

#ifndef __BabylonClicker__LayerFactory__
#define __BabylonClicker__LayerFactory__

#include "cocos2d.h"
#include "AbstructComponentFactory.h"

using namespace cocos2d;

class LayerFactory : public AbstructComponentFactory
{
public:
    LayerFactory();
    virtual ~LayerFactory();
    CREATE_FUNC(LayerFactory);
    virtual Node* createObject(const ValueMap& defBody, const ValueMap& uiData);
};

#endif /* defined(__BabylonClicker__LayerFactory__) */
