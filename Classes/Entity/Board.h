#ifndef BOARD_H_
#define BOARD_H_

#include "cocos2d.h"
#include "Dot.h"
#include "../VisibleRect.h"
#include "../Random.h"
#include "../StateMachine.h"
#include "Line.h"
#include "set"
#include "queue"
#include "algorithm"
#include "map"
#include "../AssetManager.h"
#include "../Formatter.h"

using namespace std;
USING_NS_CC;

class BoardListener {
public:

	virtual void onDotSwitchComplete() {
	}
	virtual void onDotChangeColorComplete() {
	}
	virtual void onDotRemoveComplete() {
	}

	virtual void onDotsConnected(int dotCount) {
	}
	virtual void onDotsConnectedInConnection(int dotCount) {
	}

	virtual void onDotSelected(Dot* dot, int dotsInSelection) {

	}

	virtual ~BoardListener() {
	}
};

class Board: public CCNode, public DotListener, public AssetManager {
public:

	static Board* create(int rows, int columns);

	virtual const char* getResourceDirectory() {
		return "Game";
	}

	virtual void onTouch(Dot* dot, const CCPoint& position);
	virtual void onMoveTouch(Dot* dot, const CCPoint& position);
	virtual void onEndTouch(Dot* dot, const CCPoint& position);

	void switchDotWith(Dot* dot);
	void changeDotColorWithRandom();
	void chooseDotToRemove();
	void startMultiColorConnect(DotColor c1, DotColor c2);
	void stopMultiColorConnect();

	void addListener(BoardListener* listener);

	void drawBackground();

	virtual ~Board();

private:

	float rowDotDistance;

	int rows, columns;

	std::set<Dot*> connectionDots;
	Dot* currentDot;

	Dot* swapDot;

	std::vector<BoardListener*> listeners;

	float dotRadius;

	StateMachine stateMachine;

	ccColor3B backgroundColor;

	std::set<Dot*> findOuterDotsUsingBFS();

	std::vector<Dot*> neighborsOf(Dot* dot);

	bool initWithSize(int rows, int columns);

	Dot* dotAt(int row, int column);

	int tagOf(int row, int column);
	bool isInConnection(Dot* dot);

	void onConnectingComplete(std::set<Dot*> dotsToRemove);

	void onConnectionComplete(std::set<Dot*> dotsToRemove);

	void replaceDots(std::set<Dot*> dotsToReplace);
	void addDots();
	Dot* findDotAt(const CCPoint& position);
	float getDotRowDistance();

	template<typename Func>
	void forEachDot(Func func) {
		for (int row = 1; row <= rows; row++) {
			for (int column = 1; column <= columns; column++) {
				func(dotAt(row, column));
			}
		}
	}

	Dot* addDotWithRandomColor(int row, int column, const CCPoint& position);
	void lightOnAllDots();
	void lightOffAllDots();

	void lightOnBoard();
	void lightOffBoard();

};

#endif /* BOARD_H_ */
