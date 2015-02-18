//
//  UCAnimation.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/11.
//
//

#include "UCAnimation.h"
#include "Utility.h"

Point UCAnimation::getRotatePoint(Point from, float distance, float degree) {
    float radian = CC_DEGREES_TO_RADIANS(degree);
    float x = distance * cos(radian);
    float y = distance * sin(radian);
    Point point = Point(from.x+x, from.y+y);
    return point;
}

ActionInterval* UCAnimation::getDamageAction(Point from) {
    int degree = Utility::getRandomInt(360);
    int length = 30;
    Point destination = UCAnimation::getRotatePoint(from, length, degree);
    auto go = MoveTo::create(0.3f, destination);
    auto back = MoveTo::create(0.3f, from);
    Sequence* sequence = Sequence::create(go, back, NULL);
    EaseElasticOut* elasticOut = EaseElasticOut::create(sequence);
    
    return elasticOut;
}

ActionInterval* UCAnimation::getAttackAction(Point from, Point to) {
    int length = 30;
    Point delta = (to - from).normalize();
    Point destination = Point(length*delta.x + from.x, length*delta.y + from.y);
    auto go = MoveTo::create(0.05f, destination);
    auto back = MoveTo::create(0.05f, from);
    Sequence* sequence = Sequence::create(go, back, NULL);
    return sequence;
}