#include "Dot.h"
#include "../VisibleRect.h"
#include "../Random.h"

Dot* Dot::create(float radius, DotColor color) {
	auto dot = new Dot();
	if (dot->init(radius, color)) {
		dot->autorelease();
	}
	return dot;
}

Dot* Dot::createWithRandomColor(float radius) {
	auto dot = new Dot();
	if (dot->initWithRandomColor(radius)) {
		dot->autorelease();
	}
	return dot;
}

Dot::~Dot() {
}

bool Dot::initWithRandomColor(float radius) {
	int colorIndex = Random::valueBetween(0, DOT_COLOR_COUNT);
	return init(radius, static_cast<DotColor>(colorIndex));
}

bool Dot::init(float radius, DotColor color) {
	if (!CCDrawNode::init()) {
		return false;
	}
	this->originalColor = color;
	this->radius = radius;

	setColor(color);
	setContentSize(CCSizeMake(radius * 2.0f, radius * 2.0f));

	return true;
}

void Dot::setColor(enum DotColor color) {
	this->color = color;
	clear();
	drawDot(CCPointZero, radius, createColor(color));
}

void Dot::onEnter() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, 0, true);
	CCDrawNode::onEnter();
}

void Dot::onExit() {
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCDrawNode::onExit();
}

bool Dot::ccTouchBegan(CCTouch* touch, CCEvent* event) {

	bool isTouched = boundingRect().containsPoint(touch->getLocation());

	if (isTouched) {
		listener->onTouch(this, touch->getLocation());
	}
	return isTouched;
}

void Dot::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	if (listener) {
		listener->onMoveTouch(this, touch->getLocation());
	}
}

void Dot::ccTouchEnded(CCTouch* touch, CCEvent* event) {
	if (listener) {
		listener->onEndTouch(this, touch->getLocation());
	}
}

void Dot::setListener(DotListener* listener) {
	this->listener = listener;
}

void Dot::swapWith(Dot* dot) {
	auto color = dot->getColor();
	dot->setColor(getColor());
	setColor(color);
}

void Dot::changeColorWithRandom() {
	int colorIndex = Random::valueBetween(0, DOT_COLOR_COUNT);
	auto color = static_cast<DotColor>(colorIndex);
	setColor(color);
}

void Dot::slideBy(const CCPoint& delta) {
	runAction(CCEaseBounceInOut::create(CCMoveBy::create(0.2f, delta)));
}

void Dot::bounce() {
	auto moveRight = CCSpawn::create(CCScaleTo::create(0.2, 1.2f),
			CCMoveBy::create(0.2f, ccp(10.0f, 0)), NULL);
			auto moveBack = CCSpawn::create(CCScaleTo::create(0.2, 1.0f),
					CCMoveBy::create(0.2f, ccp(10.0f, 0)), NULL);
			runAction(
					CCSequence::create(moveRight,
							CCMoveBy::create(0.2f, ccp(-20.0f, 0)),
							moveBack, NULL));
		}

void Dot::animateDotColorChange() {
	stopAllActions();
	auto action = CCRepeatForever::create(
			CCSequence::create(CCDelayTime::create(0.5f),
					CCCallFunc::create(this,
							callfunc_selector(Dot::changeToNextColor)), NULL));
	runAction(action);
}

void Dot::allowConnectionToColor(enum DotColor color) {
	originalColor = getColor();
	connectionColors.push_back(color);
	if (connectionColors.size() > 1) {
		animateDotColorChange();
	}
}

void Dot::removeConnectionColors() {
	stopAllActions();
	setColor(originalColor);
	connectionColors.clear();
	connectionColors.push_back(getColor());
}

void Dot::changeToNextColor() {
	auto it = std::find(connectionColors.begin(), connectionColors.end(),
			getColor());
	int newColorIndex = it - connectionColors.begin() + 1;
	if (newColorIndex >= connectionColors.size()) {
		newColorIndex = 0;
	}
	setColor(connectionColors[newColorIndex]);
}

void Dot::connectTo(Dot* dot) {

	addChild(
			Line::create(convertToNodeSpace(getPosition()),
					convertToNodeSpace(dot->getPosition()),
					createColor(dot->getColor())));

	auto found = std::find(connections.begin(), connections.end(), dot);
	if (found != connections.end()) {
		return;
	}

	auto res = std::find(connectionColors.begin(), connectionColors.end(),
			dot->getOriginalColor());

	if (res == connectionColors.end()) {
		return;
	}

	connections.push_back(dot);
}

bool Dot::canConnectTo(Dot* dot) {
	if (isForbiddenColor(dot)) {
		return false;
	}
	return isNextTo(dot);
}

void Dot::lightOn() {
	auto lightUpChild = CCDrawNode::create();
	lightUpChild->drawDot(CCPointZero, radius + radius * (1.0f / 2.0f),
			createColor(DotColor::GLOW));
	lightUpChild->setScale(0.5f);
	addChild(lightUpChild, -1, LIGH_UP_DOT_TAG);
	lightUpChild->runAction(
			CCEaseBounceIn::create(CCScaleTo::create(0.3, 1.0f)));
}

void Dot::lightOff() {
	getChildByTag(LIGH_UP_DOT_TAG)->removeFromParentAndCleanup(true);
}

bool Dot::isForbiddenColor(Dot* dot) {
	return std::find(connectionColors.begin(), connectionColors.end(),
			dot->getColor()) == connectionColors.end();
}

bool Dot::isNextTo(Dot* dot) {
	int row = getRow();
	int column = getColumn();

	int otherRow = dot->getRow();
	int otherColumn = dot->getColumn();

	if (otherRow - 1 == row || otherRow + 1 == row || otherRow == row) {
		if (otherColumn - 1 == column || otherColumn + 1 == column
				|| otherColumn == column) {
			return true;
		}
	}
	return false;
}

Dot::Dot() :
		listener(nullptr), radius(0.0f), color(DotColor::BLUE), originalColor(
				DotColor::BLUE), row(0), column(0) {
}

CCRect Dot::boundingRect() {
	return CCRectMake(
			boundingBox().origin.x - radius,
			boundingBox().origin.y - radius,
			boundingBox().size.width,
			boundingBox().size.height );
}
