#include "AppDelegate.h"
//#include "MenuScene.h"
#include "GameVars.h"
//#include "SoundUtil.h"
#include "Preload.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Cocos2dxStore.h"
#include "soomlaEventHandler.h"
#include "GameStoreAssets.h"
#endif


USING_NS_CC;

AppDelegate::AppDelegate() {
    srand((unsigned int)time(NULL));
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    // We initialize CCStoreController and the event handler before
    // we open the store.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GameStoreAssets *assets = GameStoreAssets::create();
    CCDictionary *storeParams = CCDictionary::create();
    storeParams->
    setObject(CCString::create("ExamplePublicKey"), "androidPublicKey");
    storeParams->
    setObject(CCString::create("ExampleCustomSecret"), "customSecret");
    
    CCString *soomSec = CCString::create("ExampleSoomSecret");
    soomla::CCStoreController::sharedStoreController()->setSoomSec(soomSec);
    
    // This is the call to initialize CCStoreController
    soomla::CCStoreController::initShared(assets, storeParams);
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Lemonade Jack");
        director->setOpenGLView(glview);
    }
    
    //SoundUtil::preloadSounds("sfx.plist");
    //SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    //cache->addSpriteFramesWithFile("studio/NewUI20.plist");
    //cache->addSpriteFramesWithFile("people/male/male0.plist");
    // turn on display FPS
#ifdef _DEBUG
    director->setDisplayStats(true);
#endif
//    director->setContentScaleFactor(0.2);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    soomla::CCSoomla::sharedSoomla()->addEventHandler(new GamePurchaseHandler());
#endif
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
//    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx/click.mp3");
//    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx/horn.mp3");
    
    // create a scene. it's an autorelease object
    auto scene = PreloadLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    
    GlobalVars::SaveGame();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Director::getInstance()->stopAnimation();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->pause();
#endif

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Director::getInstance()->startAnimation();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->resume();
#endif

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
