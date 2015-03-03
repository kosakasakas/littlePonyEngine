//
//  Observer.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef BabylonClicker_Observer_h
#define BabylonClicker_Observer_h

#include "cocos2d.h"

using namespace cocos2d;

class Observer {
public:
    Observer(){};
    virtual ~Observer(){};
    virtual void onNotice(Ref* sender) = 0; // must overrride this method.
    //virtual Ref* getRef() = 0; // 仮想継承するとautorelease()などの関数で衝突するので、必ず自身の参照を返す実装をここに入れる。
};

#endif
