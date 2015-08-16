#include "StoreScene.h"

Store::~Store() {
}

void Store::onExitPressed(CCObject* sender) {
	playSoundEffect("ButtonClick");
	GameManager::sharedGameManager()->runScene(MainMenu::scene());
}

void Store::onBuyPressed(CCObject* sender) {
	Order order;
	order.addItem(InventoryItem(SWAP_BONUS_IDENTIFIER, swapBonusQuantity));
	order.addItem(InventoryItem(CHANGE_BONUS_IDENTIFIER, changeBonusQuantity));
	order.addItem(InventoryItem(REMOVE_BONUS_IDENTIFIER, removeBonusQuantity));
	gameSpice->order(order);
}

void Store::updateTotal() {
	totalPriceLabel->setString(Formatter::toString("%d", getTotalOrderPrice()));
}

int Store::getTotalOrderPrice() {
	return swapBonusQuantity * SWAP_BONUS_PRICE
			+ changeBonusQuantity * CHANGE_BONUS_PRICE
			+ removeBonusQuantity * REMOVE_BONUS_PRICE;
}

void Store::addHeader() {
	addChild(sprite("ShoppingBag", ccp(400, 1127)));
	label("STORE")->position(ccp(385, 980))->addTo(this);
}

bool Store::init() {
	if (!CCLayer::init()) {
		return false;
	}

	gameSpice = GameSpice::getInstance();

	addHeader();

	auto exitButton = CCMenuItemSprite::create(globalSprite("ExitButton"),
			globalSprite("ExitButtonPressed"), this,
			menu_selector(Store::onExitPressed));
	exitButton->setPosition(ccp(225, 165));

	addChild(sprite("BuyBonusButton", ccp(670, 810)));
	addChild(sprite("BuyBonusButton", ccp(670, 640)));
	addChild(sprite("BuyBonusButton", ccp(670, 470)));

	auto buySwapBonusButton = CCMenuItemLabel::create(
			label(Formatter::toString("x%d", swapBonusQuantity))->getLabel(),
			this, menu_selector(Store::onBuySwapBonusButtonPressed));
	buySwapBonusButton->setPosition(ccp(670, 810));
	auto buyChangeBonusButton = CCMenuItemLabel::create(
			label(Formatter::toString("x%d", changeBonusQuantity))->getLabel(),
			this, menu_selector(Store::onBuyChangeBonusButton));
	buyChangeBonusButton->setPosition(ccp(670, 640));
	auto buyRemoveBonusButton = CCMenuItemLabel::create(
			label(Formatter::toString("x%d", removeBonusQuantity))->getLabel(),
			this, menu_selector(Store::onBuyRemoveBonusButton));
	buyRemoveBonusButton->setPosition(ccp(670, 470));

	CCMenu* menu = CCMenu::create(buySwapBonusButton, buyChangeBonusButton,
			buyRemoveBonusButton, exitButton,
			menuItemSprite("BuyButton", this,
					menu_selector(Store::onBuyPressed), ccp(575, 165)),NULL);
	menu->setPosition(CCPointZero);
	addChild(menu);

	auto drawNode = CCDrawNode::create();

	drawNode->drawDot(ccp(70, 1230), 20.0f, toColor4F(ccWHITE));
	gameSpice->getFund(
			[&] (Fund fund) {
				label(Formatter::toString("%d", fund.getAmount()))->size(28)->position(ccp(70, 1180))->addTo(this);
			});

	label("SWAP")->position(ccp(250, 810))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	label("200")->position(ccp(420, 810))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	drawNode->drawDot(ccp(450, 810), 20.0f, toColor4F(ccWHITE));

	label("CHANGE")->position(ccp(250, 640))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	label("100")->position(ccp(420, 640))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	drawNode->drawDot(ccp(450, 640), 20.0f, toColor4F(ccWHITE));

	label("REMOVE")->position(ccp(250, 470))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	label("100")->position(ccp(420, 470))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	drawNode->drawDot(ccp(450, 470), 20.0f, toColor4F(ccWHITE));

	label("TOTAL")->position(ccp(250, 350))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	totalPriceLabel = label("0")->position(ccp(420, 350))->anchorPoint(ccp(1.0, 0.5f))->addTo(this);
	drawNode->drawDot(ccp(450, 350), 20.0f, toColor4F(ccWHITE));

	addChild(drawNode);

	return true;
}

void Store::draw() {
	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(STORE_BACKGROUND_COLOR));
	ccDrawSolidRect(VisibleRect::leftTop(), ccp(800, 302), toColor4F(STORE_TOTAL_BACKGROUND_COLOR));
	ccDrawSolidRect(VisibleRect::leftTop(), ccp(800, 402), toColor4F(STORE_ITEMS_BACKGROUND_COLOR));
	ccDrawSolidRect(ccp(500, VisibleRect::leftTop().y), ccp(800, 402), toColor4F(STORE_BUTTONS_BACKGROUND_COLOR));
	ccDrawSolidRect(VisibleRect::leftTop(), ccp(800, 880), toColor4F(STORE_LABEL_BACKGROUND_COLOR));
	CCLayer::draw();
}

void Store::onBuySwapBonusButtonPressed(CCObject* sender) {
	swapBonusQuantity++;
	auto label = (CCLabelTTF*) ((CCMenuItemLabel*) sender)->getLabel();
	label->setString(Formatter::toString("x%d", swapBonusQuantity));
	playSoundEffect("ButtonClick");
	updateTotal();
}

void Store::onBuyChangeBonusButton(CCObject* sender) {
	changeBonusQuantity++;
	auto label = (CCLabelTTF*) ((CCMenuItemLabel*) sender)->getLabel();
	label->setString(Formatter::toString("x%d", changeBonusQuantity));
	playSoundEffect("ButtonClick");
	updateTotal();
}

void Store::onBuyRemoveBonusButton(CCObject* sender) {
	removeBonusQuantity++;
	auto label = (CCLabelTTF*) ((CCMenuItemLabel*) sender)->getLabel();
	label->setString(Formatter::toString("x%d", removeBonusQuantity));
	playSoundEffect("ButtonClick");
	updateTotal();
}
