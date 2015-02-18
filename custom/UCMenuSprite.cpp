//
//  UCMenuSprite.cpp
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#include "UCMenuSprite.h"

UCMenuSprite::UCMenuSprite()
: CustomMenuSprite()
{}

UCMenuSprite * UCMenuSprite::create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite)
{
    return UCMenuSprite::create(normalSprite, selectedSprite, disabledSprite, NULL, NULL);
}

UCMenuSprite * UCMenuSprite::create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector)
{
    return UCMenuSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

UCMenuSprite * UCMenuSprite::create(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, Object *target, SEL_MenuHandler selector)
{
    UCMenuSprite *pRet = new UCMenuSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
    pRet->autorelease();
    return pRet;
}