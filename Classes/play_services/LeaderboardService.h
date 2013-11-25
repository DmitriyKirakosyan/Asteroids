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

//namespace CocosDenshion {
//    
//    class TypeInfo
//    {
//    public:
//        virtual long getClassTypeInfo() = 0;
//    };
//    
//    static inline unsigned int getHashCodeByString(const char *key)
//    {
//        unsigned int len = strlen(key);
//        const char *end=key+len;
//        unsigned int hash;
//        
//        for (hash = 0; key < end; key++)
//        {
//            hash *= 16777619;
//            hash ^= (unsigned int) (unsigned char) toupper(*key);
//        }
//        return (hash);
//    }

    /**
     @class          SimpleAudioEngine
     @brief          offer a VERY simple interface to play background music & sound effect
     */
    
class EXPORT_DLL LeaderboardService
{
    public:
        void showLeaderboards();
        
        static LeaderboardService* sharedLeaderboard();
        
};
    
//} // end of namespace CocosDenshion


#endif
