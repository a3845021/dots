#ifndef DOT_H_
#define DOT_H_

#include "cocos2d.h"
#include "vector"
#include "algorithm"
#include "../Constants.h"
#include "set"
#include "../Random.h"
#include "Line.h"

USING_NS_CC;
using namespace std;

class Dot;
class Connection;

class DotListener {

public:
	virtual void onTouch(Dot* dot, const CCPoint& position) = 0;
	virtual void onMoveTouch(Dot* dot, const CCPoint& position) {}
	virtual void onEndTouch(Dot* dot, const CCPoint& position) {}

	virtual ~DotListener() {
	}
};

class Dot: public CCDrawNode, public CCTargetedTouchDelegate {
public:

	static const int LIGH_UP_DOT_TAG = 10;

CC_SYNTHESIZE_READONLY(DotColor, originalColor, OriginalColor)

CC_SYNTHESIZE_READONLY(vector<Dot*>, connections, Connections)

CC_SYNTHESIZE_READONLY(DotColor, color, Color)

CC_SYNTHESIZE(int, row, Row)

CC_SYNTHESIZE(int, column, Column)

	Dot();

	static Dot* create(float radius, DotColor color);
	static Dot* createWithRandomColor(float radius);

	void setColor(enum DotColor color);

	void changeColorWithRandom();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void lightOn();
	void lightOff();

	void bounce();

	void slideBy(const CCPoint& delta);

	void swapWith(Dot* dot);

	void setListener(DotListener* listener);

	void allowConnectionToColor(enum DotColor color);
	void removeConnectionColors();

	void connectTo(Dot* dot);

	bool canConnectTo(Dot* dot);

	CCRect boundingRect();

	virtual ~Dot();

private:

	float radius;
	DotListener* listener;

	vector<DotColor> connectionColors;

	bool init(float radius, DotColor color);
	bool initWithRandomColor(float radius);

	bool isNextTo(Dot* dot);

	void changeToNextColor();

	bool isForbiddenColor(Dot* dot);
	void animateDotColorChange();
};

#endif /* DOT_H_ */
