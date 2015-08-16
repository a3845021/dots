#include "PauseScene.h"

bool Pause::init() {
	if (!CCLayer::init()) {
		return false;
	}

	auto soundManager = SoundManager::sharedSoundManager();

	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	auto purpleDotNode = CCDrawNode::create();
	purpleDotNode->drawDot(CCPointZero, 280,
			toColor4F(PURPLE_BACKGROUND_DOT_COLOR));
	purpleDotNode->setPosition(ccp(400, 950));
	addChild(purpleDotNode);
	label("PAUSE")->size(102)->position(ccp(400, 950))->addTo(this);

	auto blueDotNode = CCDrawNode::create();
	blueDotNode->drawDot(CCPointZero, 280,
			toColor4F(BLUE_BACKGROUND_DOT_COLOR));
	blueDotNode->setPosition(ccp(400, 370));
	addChild(blueDotNode);

	auto resumeButtonPosition = ccp(400, 410);
	auto resumeButton = CCMenuItemSprite::create(globalSprite("GreenButton"),
			globalSprite("GreenButtonPressed"), this,
			menu_selector(Pause::onResumePressed));
	resumeButton->setPosition(resumeButtonPosition);
	auto exitButtonPosition = ccp(400, 310);
	auto exitButton = CCMenuItemSprite::create(globalSprite("RedButton"),
			globalSprite("RedButtonPressed"), this,
			menu_selector(Pause::onMainMenuPressed));
	exitButton->setPosition(exitButtonPosition);

	auto menu = CCMenu::create(resumeButton, exitButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	label("RESUME")->position(resumeButtonPosition)->size(48)->addTo(this);
	label("MAIN MENU")->position(exitButtonPosition)->size(48)->addTo(this);

	return true;
}

void Pause::draw() {
	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(BACKGROUND_COLOR));
	CCLayer::draw();
}

Pause::~Pause() {
}

void Pause::onResumePressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
}

void Pause::onMainMenuPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(MainMenu::scene());
}
