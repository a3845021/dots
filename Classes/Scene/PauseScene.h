#ifndef PAUSESCENE_H_
#define PAUSESCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

class Pause: public cocos2d::CCLayer, public AssetManager {
public:
	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "Pause";
	}

	void draw();

	SCENE_FUNC(Pause)
	CREATE_FUNC(Pause)
	virtual ~Pause();

private:

	void onResumePressed(CCObject* sender);
	void onMainMenuPressed(CCObject* sender);
};

#endif /* PAUSESCENE_H_ */
