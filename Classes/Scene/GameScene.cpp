#include "GameScene.h"

bool Game::init() {
	if (!CCLayer::init()) {
		return false;
	}

	auto director = CCDirector::sharedDirector();
	auto visibleSize = director->getVisibleSize();

	score = 0;

	board = Board::create(6, 6);
	board->addListener(this);
	addChild(board);

	bonusLayer = BonusLayer::create();
	bonusLayer->setPosition(
			ccp(VisibleRect::left().x, VisibleRect::rightTop().y - visibleSize.height / 7 - bonusLayer->getContentSize().height));
	bonusLayer->setVisible(false);

	addChild(bonusLayer, 2);

	gameSpice = GameSpice::getInstance();
	gameSpice->getInventory([&] (Inventory inventory) {

		auto items = inventory.getItems();
		swapRemaining = items.at(SWAP_BONUS_IDENTIFIER).getQuantity();
		removeRemaining = items.at(REMOVE_BONUS_IDENTIFIER).getQuantity();
		changeRemaining = items.at(CHANGE_BONUS_IDENTIFIER).getQuantity();

		initGUI();

		timer = CountDownTimer::create(1.0f, LEVEL_TIME);
		timer->retain();
		timer->addDelegate(this);
		timer->start();
	});

	return true;
}

void Game::draw() {
	CCLayer::draw();
	drawBackground();
	drawStatusGUI();
}

Game::~Game() {
	CC_SAFE_RELEASE(timer);
}

void Game::drawBackground() {
	board->drawBackground();
}

void Game::drawStatusBar(const CCSize& visibleSize) {
	ccDrawSolidRect(VisibleRect::leftTop(),
			ccp(VisibleRect::rightTop().x, VisibleRect::rightTop().y - visibleSize.height / 7),
			ccc4f(52.0f / 255.0f, 152.0f / 255.0f, 219.0f / 255.0f, 1.0f));
		}

void Game::drawInventory(const CCSize& visibleSize) {
	ccDrawSolidRect(VisibleRect::leftBottom(),
			ccp(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y + visibleSize.height / 8),
			ccc4f(1.0f, 1.0f, 1.0f, 1.0f));
		}

void Game::drawStatusGUI() {
	auto director = CCDirector::sharedDirector();
	auto visibleSize = director->getVisibleSize();
	drawStatusBar(visibleSize);
	drawInventory(visibleSize);
}

void Game::initInventory(const CCSize& visibleSize) {
	auto labelHeight = VisibleRect::bottom().y + visibleSize.height / 10;

	inventoryDot = Dot::createWithRandomColor(visibleSize.width / 28.0f);
	inventoryDot->setPosition(
			ccp(VisibleRect::center().x - visibleSize.width / 3.5f,
					VisibleRect::bottom().y + visibleSize.height / 22));
	addChild(inventoryDot);

}

void Game::addMenu(const CCSize& visibleSize) {

	auto labelHeight = VisibleRect::bottom().y + visibleSize.height / 10;

	label("SWAP")->size(48)->position(
			ccp(VisibleRect::center().x - visibleSize.width / 3.5f, labelHeight))->color(GRAY_TEXT)->addTo(
					this);

	auto swapBonusButton = menuItemSprite("BonusButton", this,
			menu_selector(Game::onSwitchBonusPressed),
			ccp(VisibleRect::center().x - visibleSize.width / 3.5f, 70));

	disableIfNoBonusRemaining(swapRemaining, swapBonusButton);

	label("REMOVE")->size(48)->position(
			ccp(VisibleRect::center().x + visibleSize.width / 3.5f, labelHeight))->color(GRAY_TEXT)->addTo(this);

	removeBonusCountLabel =
			label(Formatter::toString("x%d", removeRemaining))->size(48)->position(
					ccp(VisibleRect::center().x + visibleSize.width / 3.5f,
							VisibleRect::bottom().y + visibleSize.height / 22))->color(GRAY_TEXT)->addTo(this);

	auto removeBonusButton = menuItemSprite("BonusButton", this,
			menu_selector(Game::onRemoveBonusPressed),
			ccp(VisibleRect::center().x + visibleSize.width / 3.5f,
					70));

	disableIfNoBonusRemaining(removeRemaining, removeBonusButton);

	label("CHANGE")->size(48)->color(GRAY_TEXT)->position(
			ccp(VisibleRect::center().x, labelHeight))->addTo(this);

	changeBonusCountLabel =
			label(Formatter::toString("x%d", changeRemaining))->size(48)->position(
					ccp(VisibleRect::center().x,
							VisibleRect::bottom().y + visibleSize.height / 22))->color(GRAY_TEXT)->addTo(this);

	auto changeBonusButton = menuItemSprite("BonusButton", this,
			menu_selector(Game::onChangeBonusPressed),
			ccp(VisibleRect::center().x, 70));
	disableIfNoBonusRemaining(changeRemaining, changeBonusButton);

	auto resetButton = CCMenuItemSprite::create(sprite("Reset"),
			sprite("Reset"), this, menu_selector(Game::onResetPressed));
	resetButton->setPosition(
			ccp(VisibleRect::left().x + visibleSize.width / 11, VisibleRect::top().y - visibleSize.height / 12));
	auto pauseButton = CCMenuItemSprite::create(sprite("Pause"),
			sprite("Pause"), this, menu_selector(Game::onPausePressed));
	pauseButton->setPosition(
			ccp(VisibleRect::right().x - visibleSize.width / 11, VisibleRect::top().y - visibleSize.height / 12));
	auto menu = CCMenu::create(swapBonusButton, removeBonusButton,
			changeBonusButton, resetButton, pauseButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);
}

void Game::initStatusBar(const CCSize& visibleSize) {
	addChild(
			sprite("Clock",
					ccp(VisibleRect::center().x - visibleSize.width / 6.0f, VisibleRect::top().y - visibleSize.height / 20)));
					timeLabel = label("60")->size(48)->position(
							ccp(VisibleRect::center().x - visibleSize.width / 6.0f, VisibleRect::top().y - visibleSize.height / 9))->addTo(this);

					addChild(sprite("Dot",
									ccp(VisibleRect::center().x + visibleSize.width / 6.0f, VisibleRect::top().y - visibleSize.height / 20)));

					scoreLabel = label("0")->size(48)->position(
							ccp(VisibleRect::center().x + visibleSize.width / 6.0f, VisibleRect::top().y - visibleSize.height / 9))->addTo(this);
				}

void Game::initGUI() {

	auto director = CCDirector::sharedDirector();
	auto visibleSize = director->getVisibleSize();

	initStatusBar(visibleSize);
	initInventory(visibleSize);
	addMenu(visibleSize);
}

void Game::onResetPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	timer->stop();
	GameManager::sharedGameManager()->runScene(Game::scene());
}

void Game::onTimeChanged(float time) {
	timeLabel->setString(Formatter::toString("%d", time));
}

void Game::onTimeElapsed() {
	Inventory inventory;
	inventory.addItem(InventoryItem(SWAP_BONUS_IDENTIFIER, swapRemaining));
	inventory.addItem(InventoryItem(CHANGE_BONUS_IDENTIFIER, changeRemaining));
	inventory.addItem(InventoryItem(REMOVE_BONUS_IDENTIFIER, removeRemaining));
	gameSpice->updateInventory(inventory);
	auto gameSpice = GameSpice::getInstance();
	gameSpice->addFund(Fund(score), [&] (Fund f) {});
	gameSpice->getHighScore(GAMESPICE_LEADERBOARD_ID, [&] (HighScore s) {
		submitScore();
		int oldScore = s.getScore();
		bool isNewHighScore = score > oldScore;
		auto scene = isNewHighScore ? NewHighScore::scene() : GameOver::scene();
		GameManager::sharedGameManager()->runScene(scene);
	});
}

void Game::onPausePressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
}

void Game::updateBonusLabel(CCLabelTTF* label, int bonusRemaining) {
	label->setString(Formatter::toString("x%d", bonusRemaining));
}

void Game::disableIfNoBonusRemaining(int remainingBonuses, CCObject* sender) {
	if (remainingBonuses == 0) {
		auto button = (CCMenuItem*) (sender);
		button->setEnabled(false);
	}
}

void Game::onSwitchBonusPressed(CCObject* sender) {
	if (activeBonus) {
		return;
	}
	playSoundEffect("ButtonClick");
	swapRemaining--;
	activeBonus = SwitchDotBonus::create(inventoryDot, bonusLayer, board, this);
	activeBonus->start();
	disableIfNoBonusRemaining(swapRemaining, sender);
}

void Game::onChangeBonusPressed(CCObject* sender) {
	if (activeBonus) {
		return;
	}
	playSoundEffect("ButtonClick");
	changeRemaining--;
	activeBonus = ChangeDotColorBonus::create(bonusLayer, board, this);
	activeBonus->start();
	updateBonusLabel(changeBonusCountLabel, changeRemaining);
	disableIfNoBonusRemaining(changeRemaining, sender);
}

void Game::onRemoveBonusPressed(CCObject* sender) {
	if (activeBonus) {
		return;
	}
	playSoundEffect("ButtonClick");
	removeRemaining--;
	activeBonus = RemoveDotBonus::create(bonusLayer, board, this);
	activeBonus->start();
	updateBonusLabel(removeBonusCountLabel, removeRemaining);
	disableIfNoBonusRemaining(removeRemaining, sender);
}

void Game::updateScore() {
	scoreLabel->setString(Formatter::toString("%d", score));
}

void Game::onDotsConnected(int dotCount) {
	score += dotCount;
	updateScore();
}

void Game::onBonusComplete() {
	if (activeBonus) {
//		CC_SAFE_RELEASE(activeBonus);
		activeBonus = NULL;
	}
}

void Game::onDotsConnectedInConnection(int dotCount) {
	score += dotCount * 2;
	updateScore();
}

void Game::onDotSelected(Dot* dot, int dotsInSelection) {
	dot->lightOn();
}

void Game::startMultiColorBonus() {
	if (activeBonus) {
		return;
	}
	activeBonus = MultiColorBonus::create(timer, MULTI_COLOR_BONUS_TIME,
			bonusLayer, board, this);
	activeBonus->start();
}

void Game::submitScore() {
	GameSpice::getInstance()->addScore(GAMESPICE_LEADERBOARD_ID, score);
}
