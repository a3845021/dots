#include "NewHighScoreScene.h"

void NewHighScore::addMenu() {

	auto playAgainButton = CCMenuItemSprite::create(globalSprite("ResetButton"),
			globalSprite("ResetButtonPressed"), this,
			menu_selector(NewHighScore::onPlayAgainPressed));
	playAgainButton->setPosition(ccp(225, 165));
	auto leaderboardButton = CCMenuItemSprite::create(
			sprite("LeaderboardButton"), sprite("LeaderboardButtonPressed"),
			this, menu_selector(NewHighScore::onLeaderboardPressed));
	leaderboardButton->setPosition(ccp(575, 165));
	auto menu = CCMenu::create(playAgainButton, leaderboardButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
}

bool NewHighScore::init() {
	if (!CCLayer::init()) {
		return false;
	}

	label("NEW HIGH SCORE")->size(48)->position(ccp(400, 1150))->addTo(this);

	addChild(sprite("Trophy", ccp(400, 950)));

	label("YOUR SCORE IS")->size(48)->position(ccp(400, 600))->addTo(this);

	GameSpice::getInstance()->getHighScore(GAMESPICE_LEADERBOARD_ID,
			[&] (HighScore h) {
				label(Formatter::toString("%d", h.getScore()))->size(48)->position(
						ccp(360, 500))->addTo(this);
			});

	auto drawNode = CCDrawNode::create();
	drawNode->drawDot(CCPointZero, 25, toColor4F(ccWHITE));
	drawNode->setPosition(ccp(440, 500));
	addChild(drawNode);

	addMenu();
	playSoundEffect("HighScore");
	return true;
}

void NewHighScore::draw() {

	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(HIGH_SCORE_BACKGROUND_COLOR));

	ccDrawSolidRect(VisibleRect::leftTop(), ccp(VisibleRect::right().x, 350),
	toColor4F(HIGH_SCORE_SCORE_BACKGROUND_COLOR));

	ccDrawSolidRect(VisibleRect::leftTop(), ccp(VisibleRect::right().x, 750),
	toColor4F(HIGH_SCORE_LABEL_BACKGROUND_COLOR));

	CCLayer::draw();
}

NewHighScore::~NewHighScore() {
}

void NewHighScore::onPlayAgainPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(Game::scene());
}

void NewHighScore::onLeaderboardPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(GameOver::scene());
}
