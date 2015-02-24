//
//  LabelFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/23.
//
//

#ifndef __BabylonClicker__LabelFactory__
#define __BabylonClicker__LabelFactory__

#include "cocos2d.h"
#include "AbstructComponentFactory.h"

using namespace cocos2d;

class LabelFactory : public AbstructComponentFactory
{
public:
    LabelFactory();
    virtual ~LabelFactory();
    CREATE_FUNC(LabelFactory);
    virtual Node* createObject(const ValueMap& valMap, const ValueMap& uiData);
};

#endif /* defined(__BabylonClicker__LabelFactory__) */
