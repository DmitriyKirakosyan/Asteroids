
#ifndef __Test__Asteroid__
#define __Test__Asteroid__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class BaseAsteroid : public cocos2d::CCSprite
{
public:
    static BaseAsteroid* createAsteroid(CCLayer* parent, int gameSection);
    
	BaseAsteroid(CCLayer * parent, int type);

	void setRandomDirection(int gameSection);
	void setRotationTo(float x, float y);
	CCRect getHitArea();

protected:
    CCSprite* _pic1;
	CCSprite* _pic2;
    
    virtual const char* getPictFile1Name() { return "game/asteroid/blue_small_1.png"; }
    virtual const char* getPictFile2Name() { return "game/asteroid/blue_small_2.png"; }

private:
	CCLayer* _parent;

    
    static const int BASE_MAX_SPEED;
    static const int BASE_MIN_SPEED;

};

#endif /* defined(__Test__Asteroid__) */
