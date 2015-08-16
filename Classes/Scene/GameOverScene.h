#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../GameManager.h"
#include "MainMenuScene.h"
#include <functional>
#include "GameSpice.h"
USING_NS_CC;

class GameOver: public CCLayer, public AssetManager {
public:

	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "GameOver";
	}

	SCENE_FUNC(GameOver)
	CREATE_FUNC(GameOver)

	void draw();

	virtual ~GameOver();

private:

	void onPlayAgainPressed(CCObject* sender);
	void onExitPressed(CCObject* sender);
	void addMenu();
};

#endif /* GAMEOVERSCENE_H_ */
