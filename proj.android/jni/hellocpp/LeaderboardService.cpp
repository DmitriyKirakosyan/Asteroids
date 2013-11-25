#include "play_services/LeaderboardService.h"

#include <cstring>
#include <jni/JniHelper.h>
#include <jni.h>
#include "cocos2d.h"

USING_NS_CC;

/**********************************************************************************
 *   jni
 **********************************************************************************/
#define  CLASS_NAME   "com/glowmanstudio/asteroids/Test"

static LeaderboardService *s_pLeaderboard = 0;

LeaderboardService* LeaderboardService::sharedLeaderboard()
{
    if (! s_pLeaderboard)
    {
        s_pLeaderboard = new LeaderboardService();
    }

    return s_pLeaderboard;
}

void LeaderboardService::showLeaderboards()
{
    CCLog("trying to call -- %s", CLASS_NAME);
	JniMethodInfo methodInfo;
	if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showLeaderboards", "()V"))
	{
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
    CCLog("end call -- %s", CLASS_NAME);

}
