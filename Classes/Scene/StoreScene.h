#ifndef STORELAYER_H_
#define STORELAYER_H_

#include "cocos2d.h"
#include "GameSpice.h"
#include "../AssetManager.h"
#include "../Macros.h"
#include "../VisibleRect.h"
#include "../Formatter.h"
#include "MainMenuScene.h"
#include "../GameManager.h"

USING_NS_CC;

using namespace gamespice;

class Store: public CCLayer, public AssetManager {
public:

	const char* getResourceDirectory() override {
		return "Store";
	}

	bool init() override;

	void draw() override;

	SCENE_FUNC (Store)
	CREATE_FUNC(Store)

	virtual ~Store();

private:
	void onBuySwapBonusButtonPressed(CCObject* sender);
	void onBuyChangeBonusButton(CCObject* sender);
	void onBuyRemoveBonusButton(CCObject* sender);
	void onExitPressed(CCObject* sender);
	void onBuyPressed(CCObject* sender);

	void updateTotal();

	int getTotalOrderPrice();

	void addHeader();

	GameSpice* gameSpice;


	const int SWAP_BONUS_PRICE = 200;
	const int CHANGE_BONUS_PRICE = 100;
	const int REMOVE_BONUS_PRICE = 100;

	int changeBonusQuantity, removeBonusQuantity, swapBonusQuantity;

	CCLabelTTF* totalPriceLabel;

};

#endif /* STORELAYER_H_ */
