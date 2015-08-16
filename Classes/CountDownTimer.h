#ifndef TIME_H_
#define TIME_H_

#include "cocos2d.h"
#include "vector"
#include "algorithm"

USING_NS_CC;
using namespace std;

class TimerDelegate {
public:
	virtual void onTimeChanged(float time) = 0;
	virtual void onTimeElapsed() = 0;

	virtual ~TimerDelegate() {
	}
};

class CountDownTimer: public cocos2d::CCObject {

public:

	static CountDownTimer* create(float interval, float time);

	void addDelegate(TimerDelegate* delegate);
	void removeDelegate(TimerDelegate* delegate);

	void start();

	void stop();

	float getTime();

	virtual ~CountDownTimer();

private:

	float interval;
	float time;

	bool initWithUpdateInterval(float interval, float time);

	void onUpdate(float delta);

	vector<TimerDelegate*> delegates;
};

#endif /* TIME_H_ */
