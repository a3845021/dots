#include "AppDelegate.h"

#include "cocos2d.h"
#include "Scene/GameScene.h"
#include "Scene/MainMenuScene.h"
#include "Scene/NewHighScoreScene.h"
#include "Scene/GameOverScene.h"
#include "Scene/PauseScene.h"
#include "Scene/SettingsScene.h"
#include "Scene/StoreScene.h"
#include "Scene/SplashScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector *director = CCDirector::sharedDirector();
	director->setOpenGLView(CCEGLView::sharedOpenGLView());
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800, 1280,
			kResolutionExactFit);

	auto soundManager = SoundManager::sharedSoundManager();
	soundManager->onAppStarting();
//	soundManager->loadEffect("Intro");
	soundManager->loadEffect("ButtonClick");
	soundManager->loadEffect("ConnectionComplete");
	soundManager->loadEffect("HighScore");
	soundManager->loadEffect("LevelComplete");

	GameSpice::getInstance()->init(GAMESPICE_GAME_ID);

	soundManager->playLoopingBackground("Background");
	// turn on display FPS
//	pDirector->setDisplayStats(true);

// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	director->runWithScene(Splash::scene());

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
