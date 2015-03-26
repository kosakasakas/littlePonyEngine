//
//  ActionFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/26.
//
//

#include "ActionFactory.h"

ActionFactory::ActionFactory()
{
}

ActionFactory::~ActionFactory()
{
}

bool ActionFactory::init(){
    return true;
}

Action* ActionFactory::createAction(const ValueMap& body)
{
    Action* act = nullptr;
    
    // from body
    ValueMap rootAct = body.at("children").asValueVector()[0].asValueMap();
    std::string type = rootAct.at("type").asString();
    
    if (type == "easeElasticOut")
    {
        ActionInterval* actInterval = (ActionInterval*)createAction(rootAct);
        act = EaseElasticOut::create(actInterval);
    }
    else if (type == "scaleTo")
    {
        float duration = rootAct.at("duration").asFloat();
        float scale = rootAct.at("scale").asFloat();
        act = ScaleTo::create(duration, scale, scale);
    }
    else if (type == "fadeIn")
    {
        float duration = rootAct.at("duration").asFloat();
        act = FadeIn::create(duration);
    }
    else
    {
        CCLOG("required action is not defined.");
    }
    
    if (act){
        act->retain();
    }
    
    return act;
}
