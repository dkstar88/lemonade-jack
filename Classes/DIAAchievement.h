//       DIAAchievement.h
 
#ifndef __DIA_ACHIEVEMENT_H__
#define __DIA_ACHIEVEMENT_H__
 
//#include <vector>
#include "cocos2d.h"

typedef enum {
    business_level = 0,
    business_level_2 = 1,
    rep_10,
    rep_20,
    
} DIAAchievementID;
 
USING_NS_CC;
using namespace std;
 
typedef vector< DIAAchievementID > DIAAchievementIDV;
 
class DIAAchievement
{
    public:
        DIAAchievement();
        virtual ~DIAAchievement();
 
    public:
        static DIAAchievement* instance();
        virtual void release();
 
        // Unlock achievement APIs
        void unlockAchievement(DIAAchievementID id);
     
        void openGameCenter();
        void showLeaderboard();
        const DIAAchievementIDV getAllLockedAchievement();
        const DIAAchievementIDV getAllUnlockedAchievement();
    void postScore(std::string category, float score);
    
    protected:
        bool isAchievementUnlocked(DIAAchievementID id);
        const char* getIdentifierById(DIAAchievementID id);
 
    private:
        ValueMap m_pAchievementDict;
        static DIAAchievement* sInstance;
 
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    public:
        void registerAchievementController();
#endif
 
};
 
#define sGameCenter DIAAchievement::instance()
#endif // __DIA_ACHIEVEMENT_H__