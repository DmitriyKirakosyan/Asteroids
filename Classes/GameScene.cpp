#include "GameScene.h"
#include "Player.h"
#include "MapObject.h"
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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    //this->addChild(pMenu, 1);

    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    NUM_ITEMS = 0;
    MAX_TOUCHES = 3;
    DIFF_K = 50;
    

    _score = 0;
    _gameOver = false;

	_items = new std::vector<MapObject*>();
	for (int i = 0; i < NUM_ITEMS; ++i) {
		MapObject *item = new MapObject();
		item->create(i);
		this->addChild(item->getNode());
		_items->push_back(item);
		item->show();
	}

	MAX_ASTERS = 10;

	_asteroids = new std::vector<Player*>();
	for (int i = 0; i < MAX_ASTERS; ++i) {
		Player *aster = new Player();
		aster->create();
		CCParticleSystem* node = aster->getNodes()->front();
		this->addChild(node);
		_asteroids->push_back(aster);
		aster->redraw();
	}
    
    this->createAndDrawHP();

    this->setTouchEnabled(true);
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
	for (int i = 0; i < MAX_ASTERS; ++i) {
		Player* aster = _asteroids->at(i);
		aster->tick(dt);
        
        if (!aster->isLive) { _score++; }
        bool wasAlive = aster->isLive;

		aster->checkForRemove();

		if (!aster->isLive) {
			aster->removeSkin(0);
			aster->addSkin(DIFF_K);
			CCParticleSystem* node = aster->getNodes()->front();
			this->addChild(node);
			aster->redraw();
            
            //проверка на потерю хит поинта и геймовер
            if (wasAlive)
            {
                if (_lifeSprites->count() > 0)
                {
                    CCSprite* lifeItem = (CCSprite*)_lifeSprites->lastObject();
                    this->removeChild(lifeItem);
                    _lifeSprites->removeObject(lifeItem);
                }
                else
                {
                    //GAME OVER
                    this->unscheduleUpdate();
                    this->showScore();
                    _gameOver = true;
                    ScoreManager::getInstance()->saveScore(_score);
                }
            }
		}
	}
}

int GameScene::checkCollisions(MapObject *item) {
	CCRect rect1 = item->getNode()->boundingBox();
	for (unsigned i = 0; i < _player->getNodes()->size(); ++i) {
		CCRect rect2 = _player->getNodes()->at(i)->boundingBox();
		if (rect2.intersectsRect(rect1)) {
			return i;
		}
	}
	return -1;
}

void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
}

void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (_gameOver) {
        CCDirector* director = CCDirector::sharedDirector();
        director->replaceScene(MenuScene::scene());
        return;
    }
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = (CCTouch*) *it;
		CCPoint target = touch->getLocation();

		for (int i = 0; i < MAX_ASTERS; ++i) {
			Player *aster = _asteroids->at(i);
			if (!aster->isLive) { continue; }
			CCRect rect = aster->getNodes()->at(0)->boundingBox();
            
            //увеличиваем радиус тача для удобства.
            //TODO Перенести в класс Скина
            float rectW = rect.getMaxX() - rect.getMinX();
            float rectH = rect.getMaxY() - rect.getMinY();
            rect.setRect(rect.getMinX() - rectW, rect.getMinY() - rectH, rectW * 3, rectH * 3);
			if (rect.containsPoint(target)) {
				aster->isLive = false;
				DIFF_K ++;
			}
		}
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
