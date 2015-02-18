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

#ifndef CUSTOMMENUSPRITE_H
#define CUSTOMMENUSPRITE_H

#include <cocos2d.h>
USING_NS_CC;

class CustomMenuSprite : public CCMenuItemSprite
{
public:
    CustomMenuSprite();
    virtual ~CustomMenuSprite() {}
    
    static CustomMenuSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    static CustomMenuSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    static CustomMenuSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    
    /// Play a sound effect when the item is activated
    void setSoundEffect(const char *filename) { mSoundEffect = filename; }
    
    /// Override CCNode methods
    virtual void onEnter();
    virtual void onExit();
    
    /// Override CCMenuItem methods
    virtual void selected();    /// Get focus
    virtual void unselected();  /// Lost focus
    /// Override activate() to get noticed when the button is clicked
    virtual void activate();
    virtual void postponedActivate(float dt);
    
protected:
    float mOldScaleX, mOldScaleY;
    std::string mSoundEffect;
};

#endif /* CUSTOMMENUSPRITE_H */