#ifndef SETTINGSSCENE_H_
#define SETTINGSSCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

class Settings: public cocos2d::CCLayer, public AssetManager {
public:

	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "Settings";
	}

	void draw();

	SCENE_FUNC(Settings)
	CREATE_FUNC(Settings)

	virtual ~Settings();

private:

	void onMainMenuPressed(CCObject* sender);
	void onSoundEffectsPressed(CCObject* sender);
	void onBackgroundMusicPressed(CCObject* sender);

	SoundManager* soundManager;
};

#endif /* SETTINGSSCENE_H_ */
