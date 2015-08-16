#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "GameSpice.h"
#include "../Macros.h"
#include "../Constants.h"
#include "../AssetManager.h"
#include "../VisibleRect.h"
#include "../GameManager.h"
#include "../Entity/Board.h"
#include "../Entity/Dot.h"
#include "../Entity/Line.h"
#include "../Random.h"
#include "Layer/BonusLayer.h"
#include "../CountDownTimer.h"
#include "../Entity/Bonus.h"
#include "../Formatter.h"
#include "../GameManager.h"
#include "NewHighScoreScene.h"
#include "GameOverScene.h"
USING_NS_CC;

using namespace gamespice;

class Game: public cocos2d::CCLayer,
		public AssetManager,
		public TimerDelegate,
		public BoardListener,
		public BonusListener {

public:
	virtual bool init();

	virtual const char* getResourceDirectory() {
		return "Game";
	}

	virtual void onBonusComplete();

	SCENE_FUNC(Game)
	CREATE_FUNC(Game)

	virtual void onTimeChanged(float time);
	virtual void onTimeElapsed();

	virtual void onDotsConnected(int dotCount);
	virtual void onDotsConnectedInConnection(int dotCount);

	virtual void onDotSelected(Dot* dot, int dotsInSelection);

	virtual void draw();

	virtual ~Game();

private:

	Dot* inventoryDot;
	Board* board;
	BonusLayer* bonusLayer;
	CCLabelTTF* timeLabel;
	CCLabelTTF* scoreLabel;
	int score;

	CountDownTimer* timer;

	CCLabelTTF* changeBonusCountLabel;
	CCLabelTTF* removeBonusCountLabel;

	void updateScore();
	void updateBonusLabel(CCLabelTTF* label, int bonusRemaining);

	void initGUI();

	void drawBackground();
	void drawStatusGUI();
	void drawStatusBar(const CCSize& visibleSize);
	void drawInventory(const CCSize& visibleSize);
	void initInventory(const CCSize& visibleSize);
	void initStatusBar(const CCSize& visibleSize);

	void onResetPressed(CCObject* sender);
	void onPausePressed(CCObject* sender);
	void addMenu(const CCSize& visibleSize);

	void onSwitchBonusPressed(CCObject* sender);
	void onRemoveBonusPressed(CCObject* sender);
	void onChangeBonusPressed(CCObject* sender);

	void startMultiColorBonus();
	void disableIfNoBonusRemaining(int remainingBonuses, CCObject* sender);

	void submitScore();

	int swapRemaining;
	int changeRemaining;
	int removeRemaining;

	Bonus* activeBonus;

	GameSpice* gameSpice;

};

#endif /* GAMESCENE_H_ */
