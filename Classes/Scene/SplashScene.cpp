#include "SplashScene.h"

bool Splash::init() {
	if (!CCLayer::init()) {
		return false;
	}

	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	auto connectionDrawNode = CCDrawNode::create();
	connectionDrawNode->drawSegment(ccp(300, DOTS_Y_POSITION), ccp(500,DOTS_Y_POSITION), 8,toColor4F(BLUE_DOT_COLOR));
	connectionDrawNode->runAction(CCMoveBy::create(0.1f, ccp(-200.0f, 0.0f)));
	connectionDrawNode->setVisible(false);
	addChild(connectionDrawNode);

	auto clippingDrawNode = CCDrawNode::create();
	clippingDrawNode->drawSegment(ccp(0, DOTS_Y_POSITION), ccp(240, DOTS_Y_POSITION), 40, toColor4F(BACKGROUND_COLOR));
	addChild(clippingDrawNode);

	auto firstDotNode = CCDrawNode::create();
	firstDotNode->drawDot(CCPointZero, 28, toColor4F(BLUE_DOT_COLOR));
	firstDotNode->setPosition(
			ccp(300, visibleSize.height + visibleSize.height / 10));
	auto firstDotFinalPosition = ccp(300, DOTS_Y_POSITION);
	addChild(firstDotNode, 1);

	auto secondDotNode = CCDrawNode::create();
	secondDotNode->drawDot(CCPointZero, 28, toColor4F(BLUE_DOT_COLOR));

	secondDotNode->setPosition(
			ccp(500, visibleSize.height + visibleSize.height / 10));
	auto secondDotFinalPosition = ccp(500, DOTS_Y_POSITION);
	addChild(secondDotNode, 1);

	secondDotNode->runAction(
			CCSequence::create(
					CCEaseBounceInOut::create(
							CCMoveTo::create(0.7f, secondDotFinalPosition)),
					NULL));

	firstDotNode->runAction(
			CCSequence::create(CCDelayTime::create(0.5f),
					CCEaseBounceInOut::create(
							CCMoveTo::create(0.7f, firstDotFinalPosition)),
					NULL));

	connectionDrawNode->runAction(
			CCSequence::create(CCDelayTime::create(1.8f), CCShow::create(),
					CCMoveBy::create(
0.2f			, ccp(200.0f, 0.0f)), CCDelayTime::create(0.8f),
			CCCallFunc::create(this, callfunc_selector(Splash::onDotsConnected)), CCDelayTime::create(0.5f), CCRemoveSelf::create(true),
			NULL));

	playSoundEffect("Intro");

	return true;
}

void Splash::onDotsConnected() {
	auto firstGlowNodeNode = CCDrawNode::create();
	firstGlowNodeNode->drawDot(CCPointZero, 34, toColor4F(GLOW_DOT_COLOR));
	firstGlowNodeNode->setPosition(ccp(300, DOTS_Y_POSITION));

	firstGlowNodeNode->setScale(0.1f);
	firstGlowNodeNode->runAction(
			CCEaseBounceInOut::create(CCScaleTo::create(0.2f, 1.0f)));
	addChild(firstGlowNodeNode);

	auto secondGlowNodeNode = CCDrawNode::create();
	secondGlowNodeNode->drawDot(CCPointZero, 34, toColor4F(GLOW_DOT_COLOR));
	secondGlowNodeNode->setPosition(ccp(500, DOTS_Y_POSITION));

	secondGlowNodeNode->setScale(0.1f);
	secondGlowNodeNode->runAction(
			CCEaseBounceInOut::create(CCScaleTo::create(0.2f, 1.0f)));
	addChild(secondGlowNodeNode);

	auto christmasTree = sprite("ChristmasTree", ccp(400, 280));
	christmasTree->setOpacity(0.0f);
	christmasTree->runAction(
			CCSequence::create(CCDelayTime::create(1.0f),
					CCFadeIn::create(1.0f),
					CCCallFunc::create(this,
							callfunc_selector(Splash::onChristmasTreeAppeared)),
					CCDelayTime::create(3.5f),
					CCCallFunc::create(this,
							callfunc_selector(Splash::goToMainMenu)), NULL));
	addChild(christmasTree);
}

void Splash::draw() {
	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(BACKGROUND_COLOR));
	CCLayer::draw();
}

Splash::~Splash() {
}

void Splash::onChristmasTreeAppeared() {
	label("MERRY CHRISTMAS!\n HO! HO! HO!")->color(RED_DOT_COLOR)->size(48)->position(
			ccp(400.0f, 700.0f))->addTo(this);
		}

void Splash::goToMainMenu() {
	auto transition = CCTransitionMoveInR::create(0.4f, MainMenu::scene());
	GameManager::sharedGameManager()->runScene(transition);
}
