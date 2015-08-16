#include "SettingsScene.h"

bool Settings::init() {
	if (!CCLayer::init()) {
		return false;
	}

	soundManager = SoundManager::sharedSoundManager();

	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	auto blueDotNode = CCDrawNode::create();
	blueDotNode->drawDot(CCPointZero, 280,
			toColor4F(BLUE_BACKGROUND_DOT_COLOR));
	blueDotNode->setPosition(ccp(400, 950));
	addChild(blueDotNode);
	label("SETTINGS")->size(102)->position(ccp(400, 950))->addTo(this);

	label("SOUNDS EFFECTS")->position(ccp(100, 500))->anchorPoint(ccp(0.0f, 0.5f))->color(GRAY_TEXT)->addTo(this);
	label("BACKGROUND MUSIC")->position(ccp(100, 400))->anchorPoint(ccp(0.0f, 0.5f))->color(GRAY_TEXT)->addTo(this);

	auto exitButtonPosition = ccp(400, 200);
	auto exitButton = CCMenuItemSprite::create(globalSprite("GreenButton"),
			globalSprite("GreenButtonPressed"), this,
			menu_selector(Settings::onMainMenuPressed));
	exitButton->setPosition(exitButtonPosition);

	auto soundEffectsButton = CCMenuItemToggle::createWithTarget(this,
			menu_selector(Settings::onSoundEffectsPressed),
			CCMenuItemLabel::create(label("ON")->color(GRAY_TEXT)->getLabel()),
			CCMenuItemLabel::create(label("OFF")->color(GRAY_TEXT)->getLabel()),
			NULL);
	soundEffectsButton->setPosition(ccp(700, 500));
	int soundEffectsIndex = soundManager->isSoundEnabled() ? 0 : 1;
	soundEffectsButton->setSelectedIndex(soundEffectsIndex);

	auto backgroundMusicButton = CCMenuItemToggle::createWithTarget(this,
			menu_selector(Settings::onBackgroundMusicPressed),
			CCMenuItemLabel::create(label("ON")->color(GRAY_TEXT)->getLabel()),
			CCMenuItemLabel::create(label("OFF")->color(GRAY_TEXT)->getLabel()),
			NULL);
	backgroundMusicButton->setPosition(ccp(700, 400));
	int backgroundMusicIndex = soundManager->isMusicEnabled() ? 0 : 1;
	backgroundMusicButton->setSelectedIndex(backgroundMusicIndex);

	auto menu = CCMenu::create(soundEffectsButton, backgroundMusicButton,
			exitButton, NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	label("MAIN MENU")->position(exitButtonPosition)->addTo(this);

	return true;
}

void Settings::draw() {
	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(BACKGROUND_COLOR));
	CCLayer::draw();
}

Settings::~Settings() {
}

void Settings::onMainMenuPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(MainMenu::scene());
}

void Settings::onSoundEffectsPressed(CCObject* sender) {
	auto soundEffectsButton = (CCMenuItemToggle*) sender;
	if (soundEffectsButton->getSelectedIndex() == 0) {
		soundManager->unmuteSound();
	} else {
		soundManager->muteSound();
	}
	playSoundEffect("ButtonClick");
}

void Settings::onBackgroundMusicPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	auto backgroundMusicButton = (CCMenuItemToggle*) sender;
	if (backgroundMusicButton->getSelectedIndex() == 0) {
		soundManager->unmuteMusic();
	} else {
		soundManager->muteMusic();
	}
}
