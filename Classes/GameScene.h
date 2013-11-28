#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class BaseAsteroid;

class GameScene : public cocos2d::CCLayer
{
public:
    GameScene():MAX_HP(5),MAX_ASTERS(5) {
    }
    
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void onAsteroidMovingComplete(cocos2d::CCNode* pSender);

    CREATE_FUNC(GameScene);

private:
    void update(float dt);
    
    void showScore();
    
    void createAndDrawHP();
    
    BaseAsteroid* createAsteroid();

    void killLife(int count);

    const int MAX_ASTERS;
    const int MAX_HP;
    
    bool _gameOver;
    int _score;
    
    CCArray *_asteroids;
    
    CCArray* _lifeSprites;
};


#endif // __GAMESCENE_SCENE_H__
