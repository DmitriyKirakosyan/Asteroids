//
//  MenuScene.h
//  Test
//
//  Created by Dmitriy on 11/22/13.
//
//

#ifndef __Test__MenuScene__
#define __Test__MenuScene__

#include "cocos2d.h"

class MenuScene: public cocos2d::CCLayer
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MenuScene);
    
private:
    void playBtnHandler(cocos2d::CCObject* pSender);
    void playInfiniteBtnHandler(cocos2d::CCObject* pSender);
    void storeBtnHandler(cocos2d::CCObject* pSender);
    
    cocos2d::CCFiniteTimeAction* getAsteroidAnimationForBtn(cocos2d::SEL_CallFunc callback);
    
    void startGame();
    void openStore();
    
    void showScore();
};

#endif /* defined(__Test__MenuScene__) */
