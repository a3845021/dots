#ifndef SPLASHSCENE_H_
#define SPLASHSCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "MainMenuScene.h"
USING_NS_CC;

class Splash: public cocos2d::CCLayer, public AssetManager {

public:

	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "Splash";
	}

	void draw();

	SCENE_FUNC(Splash)
	CREATE_FUNC(Splash)

	virtual ~Splash();

private:

	const float DOTS_Y_POSITION = 330.0f;

	void onDotsConnected();

	void onChristmasTreeAppeared();

	void goToMainMenu();
};

#endif /* SPLASHSCENE_H_ */
