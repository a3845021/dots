#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "cocos2d.h"
#include <string>
USING_NS_CC;

static const float LEVEL_TIME = 60.0f;

static const int MULTI_COLOR_BONUS_TIME = 5;

static const char* GLOBAL_FONT = "Lato-Reg";

static const std::string GAMESPICE_GAME_ID = "52b9db0925b5c50002000001";
static const std::string GAMESPICE_LEADERBOARD_ID = "52b9db4625b5c50002000002";

static const std::string SWAP_BONUS_IDENTIFIER = "swap_bonus";
static const std::string CHANGE_BONUS_IDENTIFIER = "change_bonus";
static const std::string REMOVE_BONUS_IDENTIFIER = "remove_bonus";

static const int DEFAULT_FONT_SIZE = 48;

static const float BACKGROUND_MUSIC_VOLUME = 0.2f;
static const float SOUND_EFFECTS_VOLUME = 0.5f;

static const ccColor3B GRAY_TEXT = ccc3(149, 165, 166);
static const ccColor3B BLUE_TEXT_COLOR = ccc3(52, 152, 219);

static const ccColor3B BACKGROUND_COLOR = ccc3(236.0f, 240.0f, 241.0f);

static const ccColor3B PURPLE_DOT_COLOR = ccc3(142, 68, 173);
static const ccColor3B YELLOW_DOT_COLOR = ccc3(243, 156, 18);
static const ccColor3B BLUE_DOT_COLOR = ccc3(52, 152, 219);
static const ccColor3B RED_DOT_COLOR = ccc3(192, 57, 43);
static const ccColor3B GREEN_DOT_COLOR = ccc3(53, 190, 73);
static const ccColor3B GLOW_DOT_COLOR = ccc3(255, 255, 255);

static const ccColor3B BLUE_BACKGROUND_DOT_COLOR = ccc3(41, 128, 185);
static const ccColor3B PURPLE_BACKGROUND_DOT_COLOR = ccc3(142, 68, 173);
static const ccColor3B YELLOW_BACKGROUND_RECTANGLE_COLOR = ccc3(241, 196, 15);

/* MAIN MENU COLORS */

static const ccColor3B MAIN_MENU_BACKGROUND_COLOR = ccc3(254.0f, 253.0f,
		190.0f);
static const ccColor3B MAIN_MENU_HEADER_COLOR = ccc3(243.0f, 95.0f, 95.0f);

static const ccColor3B MAIN_MENU_STROKE_PURPLE_DOT_COLOR = ccc3(95, 53, 91);
static const ccColor3B MAIN_MENU_STROKE_YELLOW_DOT_COLOR = ccc3(164, 0, 1);
static const ccColor3B MAIN_MENU_STROKE_BLUE_DOT_COLOR = ccc3(0, 82, 156);
static const ccColor3B MAIN_MENU_STROKE_GREEN_DOT_COLOR = ccc3(52, 115, 72);

/* HIGH SCORE COLORS */

static const ccColor3B HIGH_SCORE_BACKGROUND_COLOR = ccc3(52.0f, 73.0f, 94.0f);
static const ccColor3B HIGH_SCORE_SCORE_BACKGROUND_COLOR = ccc3(167.0f, 67.0f,
		157.0f);
static const ccColor3B HIGH_SCORE_LABEL_BACKGROUND_COLOR = ccc3(243.0f, 95.0f,
		95.0f);

/* LEADERBOARD COLORS */

static const ccColor3B GAME_OVER_BACKGROUND_COLOR = ccc3(174.0f, 69.0f, 161.0f);

static const ccColor3B LEADERBOARD_ROW_BACKGROUND_COLOR = ccc3(52.0f, 73.0f,
		94.0f);
static const ccColor3B LEADERBOARD_USER_ROW_BACKGROUND_COLOR = ccc3(53.0f,
		152.0f, 219.0f);
static const ccColor3B LEADERBOARD_LINE_COLOR = ccc3(2.0f, 99.0f, 142.0f);

/* STORE COLORS */

static const ccColor3B STORE_BACKGROUND_COLOR = ccc3(52.0f, 73.0f, 94.0f);
static const ccColor3B STORE_ITEMS_BACKGROUND_COLOR = ccc3(167.0f, 67.0f,
		157.0f);
static const ccColor3B STORE_BUTTONS_BACKGROUND_COLOR = ccc3(142.0f, 68.0f,
		173.0f);
static const ccColor3B STORE_TOTAL_BACKGROUND_COLOR = ccc3(95.0f, 53.0f, 91.0f);
static const ccColor3B STORE_LABEL_BACKGROUND_COLOR = ccc3(243.0f, 95.0f,
		95.0f);

enum class DotColor
	: char {
		PURPLE = 0, YELLOW, BLUE, RED, GREEN, GLOW
};

static ccColor4F toColor4F(ccColor3B color) {
	return ccc4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f);
}

static ccColor3B getColor(DotColor source) {
	if (source == DotColor::GLOW) {
		return GLOW_DOT_COLOR;
	}
	if (source == DotColor::BLUE) {
		return BLUE_DOT_COLOR;
	}
	if (source == DotColor::YELLOW) {
		return YELLOW_DOT_COLOR;
	}
	if (source == DotColor::RED) {
		return RED_DOT_COLOR;
	}
	if (source == DotColor::PURPLE) {
		return PURPLE_DOT_COLOR;
	}
	if (source == DotColor::GREEN) {
		return GREEN_DOT_COLOR;
	}
	return GLOW_DOT_COLOR;
}

static ccColor4F createColor(DotColor source) {
	return toColor4F(getColor(source));
}

static const int DOT_COLOR_COUNT = 5;

#endif /* CONSTANTS_H_ */
