#ifndef LEADERBOARDNODE_H_
#define LEADERBOARDNODE_H_

#include "cocos2d.h"
#include "GameSpice.h"
#include "../../Constants.h"
#include "../../AssetManager.h"
#include "../../Formatter.h"
#include <string>

USING_NS_CC;
using namespace gamespice;

class LeaderboardNode: public CCNode, public AssetManager {
public:

	static LeaderboardNode* create(Leaderboard leaderboard);

	virtual const char* getResourceDirectory() {
		return "GameOver";
	}

	virtual ~LeaderboardNode();

private:

	bool init(Leaderboard leaderboard);
	void addOpponentRow(int row, Score score);
	void addPlayerRow(int row, Score score);

	int currentYOffset;
};

#endif /* LEADERBOARDNODE_H_ */
