
#include "BaseAsteroid.h"
#include "GameScene.h"


BaseAsteroid::BaseAsteroid(CCLayer * parent)
{
        CCSprite::init();
		_pic1 = CCSprite::create("game/asteroid/green_small_1.png");
        _pic2 = CCSprite::create("game/asteroid/green_small_2.png");

        this->addChild(_pic1);
        this->addChild(_pic2);

        CCFadeIn* fadein1 = CCFadeIn::create(.5);
        CCFadeOut* fadeout1 = CCFadeOut::create(.5);
        CCFadeIn* fadein2 = CCFadeIn::create(.5);
        CCFadeOut* fadeout2 = CCFadeOut::create(.5);
        CCSequence* sequence1 = CCSequence::create(fadein1, fadeout1, NULL);
        CCSequence* sequence2 = CCSequence::create(fadeout2, fadein2, NULL);
        
        CCRepeatForever* repeater1 = CCRepeatForever::create(sequence1);
        CCRepeatForever* repeater2 = CCRepeatForever::create(sequence2);
        _pic1->runAction(repeater1);
        _pic2->runAction(repeater2);

        _parent = parent;
}

void BaseAsteroid::setRandomDirection()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float randomX = CCRANDOM_0_1() * visibleSize.width;
	this->setPosition(ccp(origin.x + randomX, origin.y + visibleSize.height +
                          this->getContentSize().height/2));

	CCMoveTo* moveAction = CCMoveTo::create(5, ccp(randomX, origin.y - this->getContentSize().height/2));
	SEL_CallFuncN onMoveToPointCompleteFunc = callfuncN_selector(GameScene::onAsteroidMovingComplete);
	CCCallFuncN* onComplete = CCCallFuncN::create(_parent, onMoveToPointCompleteFunc);
	CCFiniteTimeAction* asteroidAction = CCSequence::create(moveAction, onComplete, NULL);

	this->runAction(asteroidAction);
}
