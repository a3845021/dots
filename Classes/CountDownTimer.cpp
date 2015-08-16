#include "CountDownTimer.h"

CountDownTimer* CountDownTimer::create(float interval, float time) {
	auto* timer = new CountDownTimer();
	if (timer && timer->initWithUpdateInterval(interval, time)) {
		timer->autorelease();
	} else {
		CC_SAFE_DELETE(timer);
	}
	return timer;
}

void CountDownTimer::start() {
	CCDirector* director = CCDirector::sharedDirector();
	CCScheduler* scheduler = director->getScheduler();
	scheduler->scheduleSelector(schedule_selector(CountDownTimer::onUpdate),
			this, interval, false);
}

bool CountDownTimer::initWithUpdateInterval(float interval, float time) {
	this->interval = interval;
	this->time = time;
	return true;
}

void CountDownTimer::stop() {
	CCDirector* director = CCDirector::sharedDirector();
	CCScheduler* scheduler = director->getScheduler();
	scheduler->unscheduleSelector(schedule_selector(CountDownTimer::onUpdate),
			this);
}

void CountDownTimer::addDelegate(TimerDelegate* delegate) {
	delegates.push_back(delegate);
}

float CountDownTimer::getTime() {
	return time;
}

void CountDownTimer::removeDelegate(TimerDelegate* delegate) {
	delegates.erase(find(delegates.begin(), delegates.end(), delegate));
}

void CountDownTimer::onUpdate(float delta) {
	time -= interval;
	for (auto delegate : delegates) {
		delegate->onTimeChanged(time);
	}
	if (time <= 0.0f) {
		for (auto delegate : delegates) {
			delegate->onTimeElapsed();
		}
		stop();
	}
}

CountDownTimer::~CountDownTimer() {
}
