//
//  ScoreManager.h
//  Test
//
//  Created by Dmitriy on 11/22/13.
//
//

#ifndef __Test__ScoreManager__
#define __Test__ScoreManager__

#include "cocos2d.h"

class ScoreManager
{
public:
    static ScoreManager* getInstance()
    {
        if (_instance == NULL) { _instance = new ScoreManager(); }
        return _instance;
    }
    
    ScoreManager():SCORE_KEY("score"){}

    void saveScore(int score);
    int getScore();
    
private:
    //ScoreManager();
    static ScoreManager* _instance;
    const char* SCORE_KEY;
};

#endif /* defined(__Test__ScoreManager__) */
