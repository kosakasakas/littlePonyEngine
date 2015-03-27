//
//  FSM.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/27.
//
//

#ifndef __BabylonClicker__FSM__
#define __BabylonClicker__FSM__

#include "cocos2d.h"

using namespace cocos2d;

// FSM.hはFinite Ftate Machine用の抽象関数群を提供します。

class Transition;
class TransitCondition;
class State;

class StateMap : public Ref
{
public:
    StateMap():_currentState(nullptr){};
    virtual ~StateMap()
    {
        for (auto* ref : _states){
            ((Ref*)ref)->release();
        }
    };
    virtual bool init(){
        return true;
    };
    
    void update(); // 未定義エラー回避のため実装は下に記述。
    State* getCurrentState(){ return _currentState; };
    
protected:
    State* _currentState;
    Vector<State*> _states;
};

class State : public Ref
{
public:
    State():_stateID(0){};
    virtual ~State()
    {
        for (auto* ref : _transitions){
            ((Ref*)ref)->release();
        }
    };
    
    virtual bool init(){ return true; };
    
    virtual void inState() = 0;  // State開始
    virtual void outState() = 0; // State終了
    virtual void onState() = 0;  // Satate継続
    virtual void update() = 0;
    
    State* updateTransition(); // 関数未定義エラーを回避するため実装は下に記述。
    int getStateID() { return _stateID; };
    
protected:
    int _stateID;
    Vector<Transition*> _transitions;
    
};

class Transition : public Ref
{
public:
    Transition(): _nextState(nullptr), _condition(nullptr){};
    virtual ~Transition()
    {
        ((Ref*)_nextState)->release();
        ((Ref*)_condition)->release();
    };
    
    virtual bool init(){ return true; };
    
    virtual void transit() = 0;
    virtual bool canTransit(State* state) = 0;
    virtual State* getNextState() = 0;
 
protected:
    State* _nextState;
    TransitCondition* _condition;
};

class TransitCondition : public Ref
{
public:
    TransitCondition();
    virtual ~TransitCondition();
    
    virtual bool init(){ return true; };
    
    virtual bool canTransit(State* state, const ValueMap& args) = 0;
};

void StateMap::update() {
    // 情報を更新する
    _currentState->update();
    
    // 次のStateに遷移する
    State* nextState = _currentState->updateTransition();
    if (nextState->getStateID() == _currentState->getStateID())
    {
        // currentにとどまる
        _currentState->onState();
    }
    else {
        // nextに更新
        nextState->inState();
        nextState->retain();
        _currentState->outState();
        _currentState->release();
        _currentState = nextState;
    }
};

State* State::updateTransition()
{
    // transitできるStateを上から探す。見つけた時点でtransit。
    for (auto it : _transitions) {
        Transition* t = (Transition*) it;
        if (t->canTransit(this)) {
            return t->getNextState();
        }
    }
    return nullptr;
}

#endif /* defined(__BabylonClicker__FSM__) */
