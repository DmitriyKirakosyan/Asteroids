
#include "BaseAsteroid.h"
#include "GameScene.h"
#include "GameBalance.h"
#include "GreenAsteroid.h"

const int BaseAsteroid::BASE_MAX_SPEED = 15;
const int BaseAsteroid::BASE_MIN_SPEED = 2;


BaseAsteroid* BaseAsteroid::createAsteroid(cocos2d::CCLayer *parent, int gameSection)
{
    float greenAsetrCoef = 0;
    if (gameSection > 0)
    {
        greenAsetrCoef = gameSection / 4.0;
    }
    BaseAsteroid* result;
    int type = (CCRANDOM_0_1() < greenAsetrCoef) ? 1 : 0;
    result = new BaseAsteroid(parent, type);
    
    return result;
}

BaseAsteroid::BaseAsteroid(CCLayer * parent, int type)
{
		CCSprite::init();
        if (type == 0)
        {
            _pic1 = CCSprite::create("game/asteroid/blue_small_1.png");
            _pic2 = CCSprite::create("game/asteroid/blue_small_2.png");
        }
        else
        {
            _pic1 = CCSprite::create("game/asteroid/green_small_1.png");
            _pic2 = CCSprite::create("game/asteroid/green_small_2.png");
        }

        this->addChild(_pic1);
        this->addChild(_pic2);


        float dt = .2;
        CCFadeIn* fadein1 = CCFadeIn::create(dt);
        CCFadeOut* fadeout1 = CCFadeOut::create(dt);
        CCFadeIn* fadein2 = CCFadeIn::create(dt);
        CCFadeOut* fadeout2 = CCFadeOut::create(dt);
        CCSequence* sequence1 = CCSequence::create(fadein1, fadeout1, NULL);
        CCSequence* sequence2 = CCSequence::create(fadeout2, fadein2, NULL);
        
        CCRepeatForever* repeater1 = CCRepeatForever::create(sequence1);
        CCRepeatForever* repeater2 = CCRepeatForever::create(sequence2);
        _pic1->runAction(repeater1);
        _pic2->runAction(repeater2);

        _parent = parent;
}

CCRect BaseAsteroid::getHitArea() {
	CCSize size = _pic1->getContentSize();
    size.width *= this->getScale();
    size.height *= this->getScale();
	float x = this->getPositionX() - size.width/2;
	float y = this->getPositionY() - size.height/2;
	CCRect rect = CCRectMake(x,y,size.width,size.height);
//	return CCRectApplyAffineTransform(rect, nodeToParentTransform());
	return rect;
}


void BaseAsteroid::setRandomDirection(int gameSection)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float randomX = CCRANDOM_0_1() * visibleSize.width;
	this->setPosition(ccp(origin.x + randomX, origin.y + visibleSize.height +
                          this->getContentSize().height/2));

	randomX = CCRANDOM_0_1() * visibleSize.width;
	float posY = origin.y - this->getContentSize().height/2;
    
    float maxSpeedCoef = 1.0 / GameBalance::SECTION_SPEEDS[gameSection];
    float maxSpeed  = BASE_MAX_SPEED * maxSpeedCoef;
	float speed = (maxSpeed - BASE_MIN_SPEED) * CCRANDOM_0_1() + BASE_MIN_SPEED;
	CCMoveTo* moveAction = CCMoveTo::create(speed, ccp(randomX, posY));
	this->setRotationTo(randomX, posY);
	SEL_CallFuncN onMoveToPointCompleteFunc = callfuncN_selector(GameScene::onAsteroidMovingComplete);
	CCCallFuncN* onComplete = CCCallFuncN::create(_parent, onMoveToPointCompleteFunc);
	CCFiniteTimeAction* asteroidAction = CCSequence::create(moveAction, onComplete, NULL);

	this->runAction(asteroidAction);
    
    
    //scale animation by screen fragments;
    
    CCScaleTo* scaleAnimation = CCScaleTo::create(speed, 2);
    this->runAction(scaleAnimation);
}

void BaseAsteroid::setRotationTo(float x, float y) {
	CCPoint pos = this->getPosition();
	float dx = pos.x - x;
	float dy = pos.y - y;
	float angle = atan2(dx, dy) * 180 / 3.14f;
	this->setRotation(angle);
}
