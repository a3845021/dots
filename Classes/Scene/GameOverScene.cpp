#include "GameOverScene.h"
#include "../VisibleRect.h"
#include "Node/LeaderboardNode.h"

void GameOver::addMenu() {
	auto playAgainButton = CCMenuItemSprite::create(globalSprite("ResetButton"),
			globalSprite("ResetButtonPressed"), this,
			menu_selector(GameOver::onPlayAgainPressed));
	playAgainButton->setPosition(ccp(575, 165));
	auto exitButton = CCMenuItemSprite::create(globalSprite("ExitButton"),
			globalSprite("ExitButtonPressed"), this,
			menu_selector(GameOver::onExitPressed));
	exitButton->setPosition(ccp(225, 165));
	auto menu = CCMenu::create(playAgainButton, exitButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
}

bool GameOver::init() {
	if (!CCLayer::init()) {
		return false;
	}

	label("LEADERBOARD")->size(48)->position(ccp(400, 1100))->addTo(this);

	auto gameSpice = GameSpice::getInstance();
	gameSpice->getLeaderboard(GAMESPICE_LEADERBOARD_ID,
			[&] (Leaderboard leaderboard) {
				LeaderboardNode* leaderboardNode = LeaderboardNode::create(leaderboard);
				leaderboardNode->setPosition(ccp(VisibleRect::left().x, 850));
				addChild(leaderboardNode);
			});

	addMenu();

	playSoundEffect("LevelComplete");

	return true;
}

void GameOver::draw() {

	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(GAME_OVER_BACKGROUND_COLOR));
	CCLayer::draw();
}

GameOver::~GameOver() {
}

void GameOver::onPlayAgainPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(Game::scene());
}

void GameOver::onExitPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
