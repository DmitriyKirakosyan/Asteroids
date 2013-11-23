//
//  Asteroid.h
//  Test
//
//  Created by Dmitriy on 11/24/13.
//
//

#ifndef __Test__Asteroid__
#define __Test__Asteroid__

#include "cocos2d.h"

class Asteroid : public cocos2d::CCSprite
{
public:
    Asteroid()
    {
        this->initWithFile("game/asteroid/camet.png");
    }
};

#endif /* defined(__Test__Asteroid__) */
