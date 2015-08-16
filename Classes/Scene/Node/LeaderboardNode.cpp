#include "LeaderboardNode.h"

LeaderboardNode* LeaderboardNode::create(Leaderboard leaderboard) {
	auto node = new LeaderboardNode();
	if (node && node->init(leaderboard)) {
		node->autorelease();
	} else {
		CC_SAFE_DELETE(node);
	}
	return node;
}

bool LeaderboardNode::init(Leaderboard leaderboard) {
	if (!CCNode::init()) {
		return false;
	}

	auto scores = leaderboard.getScores();

	currentYOffset = 0;

	auto gameSpice = GameSpice::getInstance();

	for (int row = 1; row <= scores.size(); row++) {
		auto score = scores[row - 1];
		if (gameSpice->isCurrentPlayer(score.getUserId())) {
			addPlayerRow(row, score);
		} else {
			addOpponentRow(row, score);
		}
	}
	return true;
}

void LeaderboardNode::addOpponentRow(int row, Score score) {
	auto backgroundNode = CCDrawNode::create();

	backgroundNode->drawSegment(ccp(0, 0), ccp(800, 0), 30.0f, toColor4F(LEADERBOARD_ROW_BACKGROUND_COLOR));
	backgroundNode->drawSegment(ccp(0, 27), ccp(800, 27), 3.0f, toColor4F(LEADERBOARD_LINE_COLOR));
	backgroundNode->setPosition(ccp(0, currentYOffset));
	addChild(backgroundNode);
	label(Formatter::toString("%d", score.getPlace()))->position(
			ccp(140, currentYOffset))->size(36)->addTo(this);
	label(Formatter::toString("%s", score.getUsername().c_str()))->position(
			ccp(400, currentYOffset))->size(36)->addTo(this);
	label(Formatter::toString("%d", score.getScore()))->position(
			ccp(660, currentYOffset))->size(36)->addTo(this);
	currentYOffset -= 60.0f;
}

void LeaderboardNode::addPlayerRow(int row, Score score) {
	auto backgroundNode = CCDrawNode::create();
	backgroundNode->drawSegment(ccp(0, -10), ccp(800, -10), 40.0f, toColor4F(LEADERBOARD_USER_ROW_BACKGROUND_COLOR));
	backgroundNode->drawSegment(ccp(0, 27), ccp(800, 27), 3.0f, toColor4F(LEADERBOARD_LINE_COLOR));
	backgroundNode->drawDot(ccp(140, -12), 32, toColor4F(PURPLE_DOT_COLOR));
	backgroundNode->setPosition(ccp(0, currentYOffset));
	addChild(backgroundNode);
	label(Formatter::toString("%d", score.getPlace()))->position(
			ccp(140, currentYOffset - 10))->size(42)->addTo(this);
	label(Formatter::toString("%s", score.getUsername().c_str()))->position(
			ccp(400, currentYOffset - 10))->size(42)->addTo(this);
	label(Formatter::toString("%d", score.getScore()))->position(
			ccp(660, currentYOffset - 10))->size(42)->addTo(this);
	currentYOffset -= 80.0f;
}

LeaderboardNode::~LeaderboardNode() {
}

