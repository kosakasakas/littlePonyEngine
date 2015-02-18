//
//  UCMenuSprite.h
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#ifndef __BabylonClicker__UCMenuSprite__
#define __BabylonClicker__UCMenuSprite__

#include <iostream>
#include "custommenusprite.h"

class UCMenuSprite : public CustomMenuSprite
{
public:
    UCMenuSprite();
    virtual ~UCMenuSprite(){};
    
    static UCMenuSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = NULL);
    static UCMenuSprite * create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector);
    static UCMenuSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Object* target, SEL_MenuHandler selector);
};

#endif /* defined(__BabylonClicker__UCMenuSprite__) */
