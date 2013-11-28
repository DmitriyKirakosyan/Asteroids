#include "GameScene.h"
#include "asteroid/BaseAsteroid.h"
#include "MenuScene.h"
#include "ScoreManager.h"
#include "play_services/LeaderboardService.h"

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


    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite *bckg = CCSprite::create("game/background_night.png");
    CCSize size = bckg->getContentSize();
    bckg->setScaleX(visibleSize.width/size.width);
    bckg->setScaleY(visibleSize.height/size.height);
    bckg->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bckg);

    this->createAndDrawHP();

    this->setTouchEnabled(true);
    this->scheduleUpdate();
    

    return true;
}

void GameScene::update(float dt) {
	for (int i = _asteroids->count(); i < MAX_ASTERS; ++i) {
		BaseAsteroid* asteroid = this->createAsteroid();
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
			BaseAsteroid *aster = (BaseAsteroid*) _asteroids->objectAtIndex(i);
			CCRect rect = aster->getHitArea();

			if (rect.containsPoint(target)) {
				CCLog("NEED TO REMOVE!!!");
				_score++;
				aster->stopAllActions();
                this->removeChild(aster);
                _asteroids->removeObject(aster);
//                asteroidsForRemove->addObject(aster);
			}
		}
		//TODO something went wrong in this code
		CCObject* asteroidForRemove;
        CCARRAY_FOREACH(asteroidsForRemove, asteroidForRemove)
        {
            ((CCSprite*)asteroidsForRemove)->stopAllActions();
            _asteroids->removeObject(asteroidForRemove);
        }
        asteroidsForRemove->removeAllObjects();
	}
}

BaseAsteroid* GameScene::createAsteroid()
{
	BaseAsteroid* result = new BaseAsteroid(this);
    result->setRandomDirection();

    return result;
}

void GameScene::onAsteroidMovingComplete(cocos2d::CCNode *pSender)
{
    this->removeChild(pSender);
    if (_asteroids->containsObject(pSender))
    {
        ((CCSprite*)pSender)->stopAllActions();
        _asteroids->removeObject(pSender);

        this->killLife(1);
    }
}

void GameScene::killLife(int count) {
	for (int i = _lifeSprites->count() - 1; i >= 0; i--) {
		CCSprite* life = (CCSprite*)_lifeSprites->objectAtIndex(i);
		this->removeChild(life);
		_lifeSprites->removeObject(life);
		count--;
		if (count <= 0) { return; }
	}
	if (_lifeSprites->count() <= 0 && !_gameOver) {
		_gameOver = true;
		showScore();
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
	ScoreManager::getInstance()->saveScore(_score);

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
