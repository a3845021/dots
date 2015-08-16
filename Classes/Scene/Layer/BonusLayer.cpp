#include "BonusLayer.h"

BonusLayer::~BonusLayer() {
}

BonusLayer* BonusLayer::create() {
	auto layer = new BonusLayer();
	if (layer && layer->init()) {
		layer->autorelease();
	}
	return layer;
}

void BonusLayer::setText(const char* text) {
	bonusLabel->runAction(
			CCSequence::create(
					CCSpawn::create(CCFadeIn::create(0.5f),
							CCMoveBy::create(0.5f, ccp(0.0f, 10.0f)),
							CCScaleTo::create(0.5f, 1.3f), NULL),
							CCMoveBy::create(0.2f, ccp(0.0f, -10.0f)),
							CCScaleTo::create(0.2f, 1.0f), NULL));
							bonusLabel->setString(text);
						}

bool BonusLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	auto director = CCDirector::sharedDirector();
	auto visibleSize = director->getVisibleSize();
	setContentSize(CCSizeMake(visibleSize.width, visibleSize.height / 10));
	CCLayerColor* background = CCLayerColor::create(ccc4(255, 255, 255, 255));
	background->setContentSize(getContentSize());

	addChild(background);

	bonusLabel =
			label("")->position(
					ccp(VisibleRect::center().x, background->getPositionY() + visibleSize.height / 20))->size(48)->color(
							GRAY_TEXT)->addTo(this);

	return true;
}
