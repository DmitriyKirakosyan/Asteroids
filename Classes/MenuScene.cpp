//
//  MenuScene.cpp
//  Test
//
//  Created by Dmitriy on 11/22/13.
//
//

#include "MenuScene.h"
#include "GameScene.h"
#include "ScoreManager.h"

USING_NS_CC;

CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init()
{
    if (!CCLayer::init()) return false;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    float partHeight = visibleSize.height / 3;
    CCMenuItemImage *playBtn = CCMenuItemImage::create("interface/menu/playBtn.png",
                                                          "interface/menu/playBtn.png",
                                                          this,
                                                          menu_selector(MenuScene::playBtnHandler));
	playBtn->setPosition(ccp(origin.x + + playBtn->getContentSize().width/2 + 50 ,
                                origin.y + 3 * partHeight - partHeight/2));

    CCMenuItemImage *playInfiniteBtn = CCMenuItemImage::create("interface/menu/playInfiniteBtn.png",
                                                       "interface/menu/playInfiniteBtn.png",
                                                       this,
                                                       menu_selector(MenuScene::playInfiniteBtnHandler));
	playInfiniteBtn->setPosition(ccp(origin.x + + playInfiniteBtn->getContentSize().width/2 + 100 ,
                             origin.y + 2 * partHeight - partHeight/2));

    CCMenuItemImage *storeBtn = CCMenuItemImage::create("interface/menu/storeBtn.png",
                                                       "interface/menu/storeBtn.png",
                                                       this,
                                                       menu_selector(MenuScene::storeBtnHandler));
	storeBtn->setPosition(ccp(origin.x + + storeBtn->getContentSize().width/2 + 150 ,
                             origin.y + partHeight/2));

    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(playBtn, playInfiniteBtn, storeBtn, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    this->showScore();

    return true;
}

void MenuScene::playBtnHandler(cocos2d::CCObject *pSender)
{
    CCFiniteTimeAction* action = getAsteroidAnimationForBtn(callfunc_selector(MenuScene::startGame));
    ((CCSprite*) pSender)->runAction(action);
}

void MenuScene::playInfiniteBtnHandler(cocos2d::CCObject *pSender)
{
    CCFiniteTimeAction* action = getAsteroidAnimationForBtn(callfunc_selector(MenuScene::startGame));
    ((CCSprite*) pSender)->runAction(action);
}

void MenuScene::storeBtnHandler(cocos2d::CCObject *pSender)
{
    CCFiniteTimeAction* action = getAsteroidAnimationForBtn(callfunc_selector(MenuScene::openStore));
    ((CCSprite*) pSender)->runAction(action);
}

CCFiniteTimeAction* MenuScene::getAsteroidAnimationForBtn(SEL_CallFunc callback)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCMoveTo *actionMove = CCMoveTo::create(1, ccp(origin.x + arc4random() % (int)visibleSize.width, origin.y + -100));
	CCFiniteTimeAction* action = CCSequence::create(actionMove, CCCallFunc::create(this, callback), NULL);
    
	return action;
}

void MenuScene::startGame()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->replaceScene(GameScene::scene());
}

void MenuScene::openStore()
{
    CCLog("Nothing here yet");
}

void MenuScene::showScore()
{
    int score = ScoreManager::getInstance()->getScore();
    if (score > 0)
    {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

        CCString* bestScoreStr = CCString::createWithFormat("best score: %d", score);
        CCLabelTTF* label = CCLabelTTF::create(bestScoreStr->getCString(), "Helvetica", 24);
        label->setPosition(ccp(origin.x + visibleSize.width - label->getContentSize().width/2 - 20,
                               origin.y + visibleSize.height/2));
        this->addChild(label);
        
        delete bestScoreStr;
    }
}