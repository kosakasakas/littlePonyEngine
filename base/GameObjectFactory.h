//
//  GameObjectFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__GameObjectFactory__
#define __BabylonClicker__GameObjectFactory__

#include <iostream>
#include "BaseObject.h"
#include "GameObject.h"

class GameObjectFactory : public virtual BaseObject
{
public:
    GameObjectFactory();
    virtual ~GameObjectFactory();
    GameObject* create(int ObjectID);
protected:
    virtual GameObject* createObject(int ObjectID) = 0;
};

#endif /* defined(__BabylonClicker__GameObjectFactory__) */
