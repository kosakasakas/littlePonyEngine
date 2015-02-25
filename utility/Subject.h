//
//  Subject.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__Subject__
#define __BabylonClicker__Subject__

#include "cocos2d.h"
#include "Observer.h"

using namespace cocos2d;

class Subject : public Ref {
public:
    Subject();
    virtual ~Subject();
    CREATE_FUNC(Subject);
    virtual bool init();
    virtual void registerObserver(Observer* o);
    virtual void removeObserver(Observer* o);
    virtual void notifyObservers(Ref* sender);
    virtual bool hasObserver(Observer* o);
protected:
    std::vector<Observer*> _observers;
};

#endif /* defined(__BabylonClicker__Subject__) */
