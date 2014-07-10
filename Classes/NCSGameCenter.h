#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface NCSGameCenter : NSObject < GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate, GKGameCenterControllerDelegate> {
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}
 
@property (assign, readonly) BOOL gameCenterAvailable;
@property (nonatomic, copy) NSString* leaderboardName;
//本地成就字典，用来保存已经下载下来的成就，以避免重复从gamecenter获取成就状态
@property (nonatomic, retain) NSMutableDictionary* achievementDictionary;
 
+ (NCSGameCenter *)sharedGameCenter;
- (void) authenticateLocalUser;
- (void) registerForAuthenticationNotification;
 
- (void) showLeaderboard;
// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error;

- (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
- (void) gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController;
//上传分数到Gamecenter
- (void) reportScore:(int64_t)score forCategory:(NSString*)category;
//从gamecenter下载前X个分数
- (void) retrieveTopXScores:(int)number;
 
- (void) showAchievementboard;
- (void) achievementViewControllerDidFinish:(GKAchievementViewController *)achievementController;
- (void) loadAchievement;
- (void) clearAchievements;
- (void) reportAchievement:(NSString*)id percent:(float)percent;
- (void) unlockAchievement:(GKAchievement*)achievement percent:(float)percent;
- (GKAchievement*) getAchievementForID:(NSString*)id;
 
@end