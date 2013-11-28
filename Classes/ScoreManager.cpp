//
//  ScoreManager.cpp
//  Test
//
//  Created by Dmitriy on 11/22/13.
//
//

#include "ScoreManager.h"
#include "cocos2d.h"
#include "play_services/LeaderboardService.h"

USING_NS_CC;

ScoreManager* ScoreManager::_instance = NULL;

int ScoreManager::getScore()
{
    CCUserDefault* userData = CCUserDefault::sharedUserDefault();
    return userData->getIntegerForKey(SCORE_KEY);
}

void ScoreManager::saveScore(int score)
{
    CCUserDefault* userData = CCUserDefault::sharedUserDefault();
    int oldScore = userData->getIntegerForKey(SCORE_KEY);
    if (score > oldScore)
    {
    	LeaderboardService::sharedLeaderboard()->updateTopScoreLeaderboard(score);
        userData->setIntegerForKey(SCORE_KEY, score);
        userData->flush();
    }
}
