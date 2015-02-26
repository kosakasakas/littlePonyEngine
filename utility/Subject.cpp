//
//  Subject.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
}

bool Subject::init() {
    return true;
}

void Subject::registerObserver(Observer* o) {
    _observers.push_back(o);
}

void Subject::removeObserver(Observer* o) {
    std::vector<Observer*>::iterator it = _observers.begin();
    while (it != _observers.end()) {
        if (*it == o) {
            it = _observers.erase(it);
        } else {
            ++it;
        }
    }
}

void Subject::notifyObservers(Ref* sender) {
    std::vector<Observer*>::iterator it = _observers.begin();
    while (it != _observers.end()) {
        Observer* o = *it;
        o->onNotice(sender);
        ++it;
    }
}

bool Subject::hasObserver(Observer* o) {
    std::vector<Observer*>::iterator it = find(_observers.begin(),_observers.end(),o);
    return (it != _observers.end());
}