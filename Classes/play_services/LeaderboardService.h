//
//  LeaderbordService.h
//  Test
//
//  Created by Dmitriy on 11/25/13.
//
//

#ifndef Test_LeaderbordService_h
#define Test_LeaderbordService_h

#include <stddef.h>
#include "Export.h"
#include <typeinfo>
#include <ctype.h>
#include <string.h>
class EXPORT_DLL LeaderboardService
{
public:
    void showLeaderboards();
    void submitScore(int score);

    static LeaderboardService* sharedLeaderboard();
    
private:
};


#endif
