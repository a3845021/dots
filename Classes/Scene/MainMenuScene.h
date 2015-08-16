#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "cocos2d.h"
#include "../Macros.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../SoundManager.h"
#include "../Random.h"
#include "../Formatter.h"
#include "SettingsScene.h"
#include "GameScene.h"
#include <vector>
#include "GameSpice.h"
#include "StoreScene.h"
USING_NS_CC;
using namespace gamespice;
class MainMenu: public cocos2d::CCLayer, public AssetManager {
public:
	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "MainMenu";
	}

	SCENE_FUNC(MainMenu)
	CREATE_FUNC(MainMenu)

	void draw();

	virtual ~MainMenu();

private:

	void onPlayPressed(CCObject* sender);
	void onScoresPressed(CCObject* sender);
	void onSettingsPressed(CCObject* sender);
	void onExitPressed(CCObject* sender);
	void addMenu();
	void addHUD();

	void onAnimationFinish();

	void drawMenuDotButtons();

	void addFund();

	const CCPoint DOT_BUTTON_GREEN_POSITION = ccp(194, 644);
	const CCPoint DOT_BUTTON_PURPLE_POSITION = ccp(606, 644);
	const CCPoint DOT_BUTTON_BLUE_POSITION = ccp(194, 250);
	const CCPoint DOT_BUTTON_YELLOW_POSITION = ccp(606, 250);
	constexpr static float DOT_BUTTON_RADIUS = 174.0f;
	constexpr static float DOT_STROKE_BUTTON_RADIUS = 176.0f;

	CCLabelTTF* titleLabel;
};

#endif /* MAINMENUSCENE_H_ */
