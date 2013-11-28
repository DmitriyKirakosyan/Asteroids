
#ifndef __Test__Asteroid__
#define __Test__Asteroid__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class BaseAsteroid : public cocos2d::CCSprite
{
public:
	BaseAsteroid(CCLayer * parent);

	void setRandomDirection();
	void setRotationTo(float x, float y);
	CCRect getHitArea();
private:
	CCLayer* _parent;

	CCSprite* _pic1;
	CCSprite* _pic2;

};

#endif /* defined(__Test__Asteroid__) */
