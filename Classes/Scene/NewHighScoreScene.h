#ifndef HIGHSCORESCENE_H_
#define HIGHSCORESCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../Formatter.h"
#include "GameOverScene.h"
USING_NS_CC;

class NewHighScore: public CCLayer, public AssetManager {
public:

	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "NewHighScore";
	}

	SCENE_FUNC(NewHighScore)
	CREATE_FUNC(NewHighScore)

	void draw();

	virtual ~NewHighScore();

private:

	void onLeaderboardPressed(CCObject* sender);
	void onPlayAgainPressed(CCObject* sender);
	void addMenu();
};

#endif /* HIGHSCORESCENE_H_ */
