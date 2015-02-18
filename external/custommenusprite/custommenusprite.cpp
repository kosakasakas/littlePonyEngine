/**
 * Copyright (C) 2012-2014 Laurent Zubiaur - pix2d.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "custommenusprite.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define SCALE_ACTION_DURATION       .4f
#define ACTIVATION_DELAY            .1f
#define SCALE_EFFECT_FACTOR         0.8f

CustomMenuSprite::CustomMenuSprite()
: CCMenuItemSprite()
, mOldScaleX(.0f)
, mOldScaleY(.0f)
{}

CustomMenuSprite * CustomMenuSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite)
{
    return CustomMenuSprite::create(normalSprite, selectedSprite, disabledSprite, NULL, NULL);
}

CustomMenuSprite * CustomMenuSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector)
{
    return CustomMenuSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

CustomMenuSprite * CustomMenuSprite::create(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
    CustomMenuSprite *pRet = new CustomMenuSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
    pRet->autorelease();
    return pRet;
}

void CustomMenuSprite::onEnter()
{
    CCMenuItemSprite::onEnter();
    mOldScaleX = getScaleX();
    mOldScaleY = getScaleY();
}

void CustomMenuSprite::onExit()
{
    stopAllActions();
    CCMenuItemSprite::onExit();
}

void CustomMenuSprite::activate()
{
    /// Activation is postponed so the scale action is not stopped when using Cocosbuilder actions with this custom button.
    /// CCMenuItemImage::activate();
    scheduleOnce(schedule_selector(CustomMenuSprite::postponedActivate), ACTIVATION_DELAY);
}

void CustomMenuSprite::postponedActivate(float dt)
{
    CCMenuItemSprite::activate();
    /// Plays the sound effect after activated
    if (mSoundEffect.length())
        SimpleAudioEngine::sharedEngine()->playEffect(mSoundEffect.c_str(),false);
}

void CustomMenuSprite::selected()
{
    CCMenuItemSprite::selected();
    runAction(CCEaseElasticOut::create(CCScaleTo::create(SCALE_ACTION_DURATION, mOldScaleX * SCALE_EFFECT_FACTOR, mOldScaleY* SCALE_EFFECT_FACTOR)));
}

void CustomMenuSprite::unselected()
{
    CCMenuItemSprite::unselected();
    runAction(CCEaseElasticOut::create(CCScaleTo::create(SCALE_ACTION_DURATION, mOldScaleX, mOldScaleY)));
}