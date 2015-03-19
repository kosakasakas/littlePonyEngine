//
//  LPMenuItemSprite.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/24.
//
//

#include "LPMenuItemSprite.h"

#define SCALE_ACTION_DURATION       0.4f
#define SCALE_EFFECT_FACTOR         0.8f

LPMenuItemSprite::LPMenuItemSprite()
: MenuItemSprite()
, _targetNode(NULL)
, _oldScaleX(0.0f)
, _oldScaleY(0.0f)
{
}

LPMenuItemSprite::~LPMenuItemSprite()
{
}

LPMenuItemSprite* LPMenuItemSprite::create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback, Node* targetNode)
{
    return create(normalSprite, selectedSprite, nullptr, callback, targetNode);
}

LPMenuItemSprite* LPMenuItemSprite::create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback, Node* targetNode)
{
    LPMenuItemSprite* pRet = new (std::nothrow) LPMenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
    pRet->autorelease();
    pRet->_targetNode = targetNode;
    return pRet;

}

void LPMenuItemSprite::onEnter() {
    MenuItemSprite::onEnter();
    Node* actionNode = (_targetNode != NULL) ? _targetNode : this;
    if (actionNode) {
        _oldScaleX = actionNode->getScaleX();
        _oldScaleY = actionNode->getScaleY();
    }
}

void LPMenuItemSprite::onExit() {
    stopAllActions();
    MenuItemSprite::onExit();
}

void LPMenuItemSprite::activate() {
    MenuItemSprite::activate();
}

void LPMenuItemSprite::selected() {
    MenuItemSprite::selected();
    Node* actionNode = (_targetNode != NULL) ? _targetNode : this;
    if (actionNode) {
        actionNode->runAction(EaseElasticOut::create(ScaleTo::create(SCALE_ACTION_DURATION, _oldScaleX * SCALE_EFFECT_FACTOR, _oldScaleY * SCALE_EFFECT_FACTOR)));
    }
}

void LPMenuItemSprite::unselected() {
    MenuItemSprite::unselected();
    Node* actionNode = (_targetNode != NULL) ? _targetNode : this;
    if (actionNode) {
        actionNode->runAction(EaseElasticOut::create(ScaleTo::create(SCALE_ACTION_DURATION, _oldScaleX, _oldScaleY)));
    }
}