#ifndef BONUSLAYER_H_
#define BONUSLAYER_H_

#include "cocos2d.h"
#include "../../VisibleRect.h"
#include "../../AssetManager.h"

USING_NS_CC;

class BonusLayer: public CCLayer, public AssetManager {
public:

	virtual const char* getResourceDirectory() {
		return "Game";
	}

	static BonusLayer* create();

	void setText(const char* text);

	virtual ~BonusLayer();

private:
	virtual bool init();

	CCLabelTTF* bonusLabel;

};

#endif /* BONUSLAYER_H_ */
