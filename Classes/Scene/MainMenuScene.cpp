#include "MainMenuScene.h"

void MainMenu::addMenu() {

	auto playButton = CCMenuItemSprite::create(sprite("PlayButton"),
			sprite("PlayButton"), this, menu_selector(MainMenu::onPlayPressed));
	playButton->setPosition(DOT_BUTTON_GREEN_POSITION);
	auto action = CCRepeatForever::create(
			CCSequence::create(
					CCEaseElasticOut::create(CCScaleTo::create(1.0f, 1.3f)),
					CCScaleTo::create(0.5f, 0.9f), CCDelayTime::create(0.5f),
					NULL));
	auto labelAction = (CCAction*) action->copy();
	playButton->runAction(action);
	label("PLAY")->position(ccp(194, 544))->size(28)->addTo(this)->runAction(labelAction);

	auto scoresButton = CCMenuItemSprite::create(sprite("ScoresButton"),
			sprite("ScoresButton"), this,
			menu_selector(MainMenu::onScoresPressed));
	scoresButton->setPosition(DOT_BUTTON_PURPLE_POSITION);

	auto wiggleAction = CCRepeatForever::create(
			CCSequence::create(CCRotateBy::create(0.3f, 10.0f),
					CCRotateBy::create(0.3f, -20.0f),
					CCRotateBy::create(0.4f, 10.0f), CCDelayTime::create(1.0f),
					NULL));

	label("SCORES")->position(ccp(606, 544))->size(28)->addTo(this)->runAction(
			wiggleAction);

	auto settingsButton = CCMenuItemSprite::create(sprite("SettingsButton"),
			sprite("SettingsButton"), this,
			menu_selector(MainMenu::onSettingsPressed));
	settingsButton->setPosition(DOT_BUTTON_BLUE_POSITION);
	settingsButton->runAction(
			CCRepeatForever::create(CCRotateBy::create(4.0f, 360.0f)));
//	label("SETTINGS")->position(ccp(194, 150))->size(28)->addTo(this);
	label("STORE")->position(ccp(194, 150))->size(28)->addTo(this);

	auto exitButton = CCMenuItemSprite::create(sprite("ExitButton"),
			sprite("ExitButton"), this, menu_selector(MainMenu::onExitPressed));
	exitButton->setPosition(DOT_BUTTON_YELLOW_POSITION);

	auto reverseWiggleAction = CCRepeatForever::create(
			CCSequence::create(CCRotateBy::create(0.3f, -10.0f),
					CCRotateBy::create(0.3f, 20.0f),
					CCRotateBy::create(0.4f, -10.0f), CCDelayTime::create(1.0f),
					NULL));

	label("EXIT")->position(ccp(606, 150))->size(28)->addTo(this)->runAction(reverseWiggleAction);

	auto menu = CCMenu::create(playButton, scoresButton, exitButton,
			settingsButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
}

void MainMenu::drawMenuDotButtons() {
	auto dotDrawNode = CCDrawNode::create();
	dotDrawNode->drawDot(DOT_BUTTON_GREEN_POSITION, DOT_STROKE_BUTTON_RADIUS,
			toColor4F(MAIN_MENU_STROKE_GREEN_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_GREEN_POSITION, DOT_BUTTON_RADIUS,
			toColor4F(GREEN_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_PURPLE_POSITION, DOT_STROKE_BUTTON_RADIUS,
			toColor4F(MAIN_MENU_STROKE_PURPLE_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_PURPLE_POSITION, DOT_BUTTON_RADIUS,
			toColor4F(PURPLE_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_BLUE_POSITION, DOT_STROKE_BUTTON_RADIUS,
			toColor4F(MAIN_MENU_STROKE_BLUE_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_BLUE_POSITION, DOT_BUTTON_RADIUS,
			toColor4F(BLUE_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_YELLOW_POSITION, DOT_STROKE_BUTTON_RADIUS,
			toColor4F(MAIN_MENU_STROKE_YELLOW_DOT_COLOR));
	dotDrawNode->drawDot(DOT_BUTTON_YELLOW_POSITION, DOT_BUTTON_RADIUS,
			toColor4F(YELLOW_DOT_COLOR));
	addChild(dotDrawNode);
}

void MainMenu::addHUD() {

	drawMenuDotButtons();

	auto gameSpice = GameSpice::getInstance();
	auto dotDrawNode = CCDrawNode::create();
	dotDrawNode->drawDot(ccp(72, 1225), 16, toColor4F(ccWHITE));
	addChild(dotDrawNode);
	gameSpice->getFund(
			[&] (Fund fund) {
				label(Formatter::toString("%d", fund.getAmount()))->size(28)->position(
						ccp(72,1185))->addTo(this);
			});

	label("LOOPS\n&\nDOTS")->size(72)->position(ccp(400, 1060))->addTo(this);
	addMenu();
}

bool MainMenu::init() {
	if (!CCLayer::init()) {
		return false;
	}

	auto gameSpice = GameSpice::getInstance();
	if (gameSpice->noRegisteredUser()) {
		User user(Formatter::toString("Dots Player %d", Random::valueBetween(1, 20000)));

		gameSpice->addUser(user, [&] (User u) {

			addFund();
		});
	} else {
		addHUD();
	}

	return true;
}

void MainMenu::draw() {
	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(BACKGROUND_COLOR));
	ccDrawSolidRect(VisibleRect::leftTop(), ccp(800, 880), toColor4F(MAIN_MENU_HEADER_COLOR));
	CCLayer::draw();
}

MainMenu::~MainMenu() {
}

void MainMenu::onPlayPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(Game::scene());
}

void MainMenu::onSettingsPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(Store::scene());
}

void MainMenu::onExitPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenu::onAnimationFinish() {
}

void MainMenu::onScoresPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(GameOver::scene());
}

void MainMenu::addFund() {
	Fund fund(1200);
	GameSpice::getInstance()->addFund(fund, [&] (Fund f) {
		Order order;
		order.addItem(InventoryItem(SWAP_BONUS_IDENTIFIER, 3));
		order.addItem(InventoryItem(CHANGE_BONUS_IDENTIFIER, 3));
		order.addItem(InventoryItem(REMOVE_BONUS_IDENTIFIER, 3));
		GameSpice::getInstance()->order(order);
		addHUD();
	});
}
