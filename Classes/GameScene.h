#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Player;
class MapObject;

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
    void update(float dt);
    int checkCollisions(MapObject *item);
    
    void showScore();
    
    void createAndDrawHP();

    int NUM_ITEMS;
    int MAX_TOUCHES;
    int MAX_ASTERS;
    
    const int MAX_HP = 5;
    
    bool _gameOver;
    int _score;
    

    std::vector<MapObject*> *_items;
    std::vector<Player*> *_asteroids;


    Player *_player;

    MapObject *_item;
    
    CCArray* _lifeSprites;
};


#endif // __GAMESCENE_SCENE_H__
