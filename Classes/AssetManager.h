#ifndef RESOURCEFINDER_H_
#define RESOURCEFINDER_H_

#include "cocos2d.h"
#include "VisibleRect.h"
#include "SoundManager.h"
#include "Constants.h"
#include <string>

USING_NS_CC;

class LabelBuilder: CCObject {
public:
	static LabelBuilder* label(const char* text, const char* font) {
		auto builder = new LabelBuilder();
		builder->init(text, font);
		builder->autorelease();
		return builder;
	}

	static LabelBuilder* label(const char* text) {
		auto builder = new LabelBuilder();
		builder->initWithGlobalFont(text);
		builder->autorelease();
		return builder;
	}

	LabelBuilder* size(int fontSize) {
		aLabel->setFontSize(fontSize);
		return this;
	}

	LabelBuilder* position(CCPoint position) {
		aLabel->setPosition(position);
		return this;
	}

	LabelBuilder* anchorPoint(CCPoint anchorPoint) {
		aLabel->setAnchorPoint(anchorPoint);
		return this;
	}

	LabelBuilder* color(ccColor3B color) {
		aLabel->setColor(color);
		return this;
	}

	LabelBuilder* opacity(int opacity) {
		aLabel->setOpacity(opacity);
		return this;
	}

	LabelBuilder* dimensions(const CCSize& dimensions) {
		aLabel->setDimensions(dimensions);
		return this;
	}

	CCLabelTTF* addTo(CCNode* node) {
		node->addChild(aLabel);
		return getLabel();
	}

	CCLabelTTF* getLabel() {
		return aLabel;
	}

private:

	void init(const char* text, const char* font) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		aLabel = CCLabelTTF::create(text, font, DEFAULT_FONT_SIZE);
#else

		aLabel = CCLabelTTF::create(text,
				CCString::createWithFormat("Fonts/%s.ttf", font)->getCString(),
				DEFAULT_FONT_SIZE);
#endif
	}

	void initWithGlobalFont(const char* text) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		aLabel = CCLabelTTF::create(text, GLOBAL_FONT, DEFAULT_FONT_SIZE);
#else
		aLabel =
				CCLabelTTF::create(text,
						CCString::createWithFormat("Fonts/%s.ttf", GLOBAL_FONT)->getCString(),
						DEFAULT_FONT_SIZE);
#endif
	}

	CCLabelTTF* aLabel;
};

class AssetManager {
public:

	CCSprite* globalSprite(const char *name) {
		const char* path = CCString::createWithFormat("Scenes/Global/%s.png",
				name)->getCString();
		return CCSprite::create(path);
	}

	void addBackground(CCNode *toNode) {
		CCSprite* background = sprite("Background", VisibleRect::center());
		toNode->addChild(background);
	}

	LabelBuilder* label(const char *text) {
		return LabelBuilder::label(text);
	}

	CCSprite* globalSprite(const char *name, CCPoint position) {
		CCSprite* sp = globalSprite(name);
		sp->setPosition(position);
		return sp;
	}

	virtual CCSprite* sprite(const char* name, CCPoint position) {
		CCSprite* sp = sprite(name);
		sp->setPosition(position);
		return sp;
	}

	virtual CCSprite* sprite(const char* name) {
		const char* imagePath = image(name);
		return CCSprite::create(image(name));
	}

	virtual CCMenuItemSprite* menuItemSprite(const char* spriteName,
			CCObject* target, SEL_MenuHandler menuHandler, CCPoint point) {
		std::string spriteString = std::string(spriteName);
		std::string spritePressedString = spriteString + "Pressed";
		auto item = CCMenuItemSprite::create(sprite(spriteName),
				sprite(spritePressedString.c_str()), target, menuHandler);
		item->setPosition(point);
		return item;
	}

	void playSoundEffect(const char *name) {
		SoundManager::sharedSoundManager()->playSoundEffect(name);
	}

	virtual ~AssetManager() {
	}

protected:

	virtual const char* getResourceDirectory() = 0;

	const char* image(const char *name) {
		return CCString::createWithFormat("Scenes/%s/%s.png",
				getResourceDirectory(), name)->getCString();
	}
};

#endif /* RESOURCEFINDER_H_ */
