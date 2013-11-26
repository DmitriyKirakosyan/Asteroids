
#include "BaseAsteroid.h"
#include "GameScene.h"


BaseAsteroid::BaseAsteroid(CCLayer * parent)
    {
		this->init();
		_pic1 = CCSprite::create("game/asteroid/greensm_1.png");
        _pic2 = CCSprite::create("game/asteroid/greensm_2.png");

        this->addChild(_pic1);
        this->addChild(_pic2);

        CCFadeOut* action1 = CCFadeOut::create(2);
        CCFadeIn* action2 = CCFadeIn::create(2);
        CCRepeatForever* repeater1 = CCRepeatForever::create(action1);
        CCRepeatForever* repeater2 = CCRepeatForever::create(action2);
        _pic1->runAction(action1);
        _pic2->runAction(action2);

        _parent = parent;
    }

void BaseAsteroid::setRandomDirection() {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float randomX = CCRANDOM_0_1() * visibleSize.width;
	this->setPosition(ccp(origin.x + randomX,
							origin.y + visibleSize.height + this->getContentSize().height/2));

	CCMoveTo* moveAction = CCMoveTo::create(5, ccp(randomX, origin.y - this->getContentSize().height/2));
	SEL_CallFuncN onMoveToPointCompleteFunc = callfuncN_selector(GameScene::onAsteroidMovingComplete);
	CCCallFuncN* onComplete = CCCallFuncN::create(_parent, onMoveToPointCompleteFunc);
	CCFiniteTimeAction* asteroidAction = CCSequence::create(moveAction, onComplete, NULL);

	this->runAction(asteroidAction);
}
