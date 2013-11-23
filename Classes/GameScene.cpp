#include "GameScene.h"
#include "Asteroid.h"
#include "MenuScene.h"
#include "ScoreManager.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _asteroids = new CCArray();
    
    _score = 0;
    _gameOver = false;

    this->createAndDrawHP();

    this->setTouchEnabled(true);
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
    
    
	for (int i = _asteroids->count(); i < MAX_ASTERS; ++i) {
        Asteroid* asteroid = this->createAsteroid();
        _asteroids->addObject(asteroid);
        
        this->addChild(asteroid);
	}
    
}

void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (_gameOver) {
        CCDirector* director = CCDirector::sharedDirector();
        director->replaceScene(MenuScene::scene());
        return;
    }
    
    CCArray* asteroidsForRemove = CCArray::create();
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = (CCTouch*) *it;
		CCPoint target = touch->getLocation();

		for (int i = 0; i < _asteroids->count(); ++i) {
			Asteroid *aster = (Asteroid*) _asteroids->objectAtIndex(i);
			CCRect rect = aster->boundingBox();

            //увеличиваем радиус тача для удобства.
            //TODO Перенести в класс Скина
            float rectW = rect.getMaxX() - rect.getMinX();
            float rectH = rect.getMaxY() - rect.getMinY();
            rect.setRect(rect.getMinX() - rectW, rect.getMinY() - rectH, rectW * 3, rectH * 3);
			if (rect.containsPoint(target)) {
                this->removeChild(aster);
                asteroidsForRemove->addObject(aster);
			}
		}
        CCObject* asteroidForRemove;
        CCARRAY_FOREACH(asteroidsForRemove, asteroidForRemove)
        {
            _asteroids->removeObject(asteroidForRemove);
        }
        asteroidsForRemove->removeAllObjects();
	}
}

Asteroid* GameScene::createAsteroid()
{
    Asteroid* result = new Asteroid();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    float randomX = CCRANDOM_0_1() * visibleSize.width;
    result->setPosition(ccp(origin.x + randomX,
                            origin.y + visibleSize.height + result->getContentSize().height/2));
    
    CCMoveTo* moveAction = CCMoveTo::create(2, ccp(randomX, origin.y - result->getContentSize().height/2));
    SEL_CallFuncN onMoveToPointCompleteFunc = callfuncN_selector(GameScene::onAsteroidMovingComplete);
    CCCallFuncN* onComplete = CCCallFuncN::create(this, onMoveToPointCompleteFunc);
    CCFiniteTimeAction* asteroidAction = CCSequence::create(moveAction, onComplete, NULL);
    
    result->runAction(asteroidAction);
    
    return result;
}

void GameScene::onAsteroidMovingComplete(cocos2d::CCNode *pSender)
{
    CCLog("asteroid was down..");
    
    this->removeChild(pSender);
    if (_asteroids->containsObject(pSender))
    {
        _asteroids->removeObject(pSender);
    }
}

void GameScene::createAndDrawHP()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    _lifeSprites = new CCArray();
    CCSprite* item;
    for (int i = 0; i < MAX_HP ; ++i)
    {
        item = CCSprite::create("interface/game/life.png");
        _lifeSprites->addObject(item);
        item->setPosition(ccp(origin.x + 50 + i * 50,
                              origin.y + visibleSize.height - 50));
        this->addChild(item);
    }
}

void GameScene::showScore()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCString* scoreString = CCString::createWithFormat("your score: %d", _score);
    CCLabelTTF* label = CCLabelTTF::create(scoreString->getCString(), "Helvetica", 24);
    label->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(label);
    delete scoreString;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
