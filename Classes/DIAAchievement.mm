//    DIAAchievement.mm
#include "DIAAchievement.h"
#include "NCSGameCenter.h"
 
DIAAchievement* DIAAchievement::sInstance = NULL;
 
DIAAchievement::DIAAchievement()
{
    this->m_pAchievementDict = FileUtils::getInstance()->getValueMapFromFile("achievements.plist");
}
 
DIAAchievement::~DIAAchievement()
{
}
 
DIAAchievement* DIAAchievement::instance()
{
    if ( sInstance == NULL )
    {
        sInstance = new DIAAchievement();
    }
 
    return sInstance;
}
 
void DIAAchievement::release()
{
    if ( sInstance )
    {
        delete sInstance;
        sInstance = NULL;
    }
}
 
void DIAAchievement::registerAchievementController()
{
    [[NCSGameCenter sharedGameCenter] authenticateLocalUser];
}
 
//公共函数，通过成就id获取成就指针
GKAchievement* getAchievementByID(const char* id)
{
    GKAchievement* pRet = NULL;
    if ( id )
    {
        NSString* identifier = [[NSString alloc] initWithUTF8String:id];
        pRet = [[NCSGameCenter sharedGameCenter] getAchievementForID:identifier];
    }
 
    return pRet;
}
 
// 打开Gamecenter面板，并将起始页定位在成就页。
void DIAAchievement::openGameCenter()
{
    [[NCSGameCenter sharedGameCenter] showAchievementboard];
}


void DIAAchievement::showLeaderboard() {
    [[NCSGameCenter sharedGameCenter] showLeaderboard];
}

void DIAAchievement::postScore(std::string category, float score) {
    NSString* identifier = [[NSString alloc] initWithUTF8String: category.c_str()];
    [[NCSGameCenter sharedGameCenter] reportScore:score forCategory:identifier];
//    [[NCSGameCenter sharedGameCenter] reportAchievement: identifier percent:score];
}

//判断成就是否已经解锁
bool DIAAchievement::isAchievementUnlocked(DIAAchievementID id)
{
    bool ret = true;
     
    const char* pIdentifier = this->getIdentifierById(id);
 
    GKAchievement* achievement = getAchievementByID(pIdentifier);
    if ( achievement )
    {
        ret = achievement.completed;
    }
    return ret;
}
 
//解锁成就
void DIAAchievement::unlockAchievement(DIAAchievementID id)
{
    const char* pIdentifier = this->getIdentifierById(id);
     
    GKAchievement* achievement = getAchievementByID(pIdentifier);
    if ( achievement != NULL && achievement.completed != YES )
    {
        [[NCSGameCenter sharedGameCenter] unlockAchievement:achievement
                                                    percent:100.0];
    }
}
 
const char* DIAAchievement::getIdentifierById(DIAAchievementID id)
{
    std::string str_id = StringUtils::format("%d", (int)id);
    if (this->m_pAchievementDict.find(str_id) != this->m_pAchievementDict.end()) {
        
    }
    const std::string pIdStr = this->m_pAchievementDict[str_id].asString();
    if ( pIdStr.size() )
    {
        return pIdStr.c_str();
    }
     
    return NULL;
}

