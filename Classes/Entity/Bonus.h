#ifndef BONUS_H_
#define BONUS_H_
#include "Board.h"
#include "../Scene/Layer/BonusLayer.h"
#include "../Scene/GameScene.h"
#include "map"
#include "../Formatter.h"
#include "Dot.h"

using namespace std;

class BonusListener {

public:
	virtual void onBonusComplete() = 0;

	virtual ~BonusListener() {
	}
};

class Bonus: public CCObject, public BoardListener {
public:

	Bonus(BonusLayer* bonusLayer, Board* board, BonusListener* listener) :
			bonusLayer(bonusLayer), board(board), listener(listener) {
		board->addListener(this);
	}

	virtual void start() {
		doStart();
	}

	virtual void stop() {
		doStop();
		if (listener) {
			listener->onBonusComplete();
		}
	}

	virtual ~Bonus() {
	}

protected:

	virtual void doStart() = 0;
	virtual void doStop() = 0;

	BonusLayer* bonusLayer;
	Board* board;

	BonusListener* listener;
};

class TimedBonus: public Bonus, public TimerDelegate {
public:
	TimedBonus(CountDownTimer* timer, int timeToRun, BonusLayer* bonusLayer,
			Board* board, BonusListener* listener) :
			Bonus(bonusLayer, board, listener), timer(timer), timeToRun(
					timeToRun), startTime(0) {
		timer->addDelegate(this);
		startTime = timer->getTime();
	}

	virtual void onTimeChanged(float time) {
		int elapsedTime = startTime - time;
		if (elapsedTime > timeToRun) {
			stop();
		}
	}
	virtual void onTimeElapsed() {
		stop();
	}

	virtual void stop() {
		timer->removeDelegate(this);
		Bonus::stop();
	}

	virtual ~TimedBonus() {
	}

protected:
	int timeToRun;
	CountDownTimer* timer;
	float startTime;
};

class MultiColorBonus: public TimedBonus {

public:
	MultiColorBonus(CountDownTimer* timer, int timeToRun,
			BonusLayer* bonusLayer, Board* board, BonusListener* listener) :
			TimedBonus(timer, timeToRun, bonusLayer, board, listener) {
	}

	static MultiColorBonus* create(CountDownTimer* timer, int timeToRun,
			BonusLayer* bonusLayer, Board* board, BonusListener* listener) {
		auto bonus = new MultiColorBonus(timer, timeToRun, bonusLayer, board,
				listener);
		if (bonus) {
			bonus->autorelease();
			bonus->retain();
		} else {
			CC_SAFE_DELETE(bonus);
		}
		return bonus;
	}

protected:
	virtual void doStart() {
		bonusLayer->setText("MULTI COLOR CONNECT");
		bonusLayer->setVisible(true);
		auto c1 = getRandomColor();
		auto c2 = getRandomColor();
		while (c1 == c2) {
			c2 = getRandomColor();
		}
		board->startMultiColorConnect(c1, c2);
	}

	virtual void doStop() {
		bonusLayer->setVisible(false);
		board->stopMultiColorConnect();
	}

private:

	DotColor getRandomColor() {
		int colorIndex = Random::valueBetween(0, DOT_COLOR_COUNT);
		return static_cast<DotColor>(colorIndex);
	}

};

class RemoveDotBonus: public Bonus {
public:
	RemoveDotBonus(BonusLayer* bonusLayer, Board* board,
			BonusListener* listener) :
			Bonus(bonusLayer, board, listener) {
	}

	static RemoveDotBonus* create(BonusLayer* bonusLayer, Board* board,
			BonusListener* listener) {
		auto bonus = new RemoveDotBonus(bonusLayer, board, listener);
		if (bonus) {
			bonus->autorelease();
			bonus->retain();
		} else {
			CC_SAFE_DELETE(bonus);
		}
		return bonus;
	}

	virtual void onDotRemoveComplete() {
		stop();
	}

protected:
	virtual void doStart() {
		bonusLayer->setText("CHOOSE DOT TO REMOVE");
		bonusLayer->setVisible(true);
		board->chooseDotToRemove();
	}

	virtual void doStop() {
		bonusLayer->setVisible(false);
	}

};

class ChangeDotColorBonus: public Bonus {
public:
	ChangeDotColorBonus(BonusLayer* bonusLayer, Board* board,
			BonusListener* listener) :
			Bonus(bonusLayer, board, listener) {
	}

	static ChangeDotColorBonus* create(BonusLayer* bonusLayer, Board* board,
			BonusListener* listener) {
		auto bonus = new ChangeDotColorBonus(bonusLayer, board, listener);
		if (bonus) {
			bonus->autorelease();
			bonus->retain();
		} else {
			CC_SAFE_DELETE(bonus);
		}
		return bonus;
	}

	virtual void onDotChangeColorComplete() {
		stop();
	}

protected:

	virtual void doStart() {
		bonusLayer->setText("CHANGE DOT COLOR");
		bonusLayer->setVisible(true);
		board->changeDotColorWithRandom();
	}

	virtual void doStop() {
		bonusLayer->setVisible(false);
	}

};

class SwitchDotBonus: public Bonus {

public:
	SwitchDotBonus(Dot* inventoryDot, BonusLayer* bonusLayer, Board* board,
			BonusListener* listener) :
			Bonus(bonusLayer, board, listener), inventoryDot(inventoryDot) {
	}

	static SwitchDotBonus* create(Dot* inventoryDot, BonusLayer* bonusLayer,
			Board* board, BonusListener* listener) {
		auto bonus = new SwitchDotBonus(inventoryDot, bonusLayer, board,
				listener);
		if (bonus) {
			bonus->autorelease();
			bonus->retain();
		} else {
			CC_SAFE_DELETE(bonus);
		}
		return bonus;
	}

	virtual void onDotSwitchComplete() {
		stop();
	}

protected:

	virtual void doStart() {
		bonusLayer->setText("CHOOSE DOT TO SWITCH");
		bonusLayer->setVisible(true);
		board->switchDotWith(inventoryDot);
	}

	virtual void doStop() {
		bonusLayer->setVisible(false);
	}

private:

	Dot* inventoryDot;

};

enum class BonusType {
	SWITCH, CHANGE, REMOVE, MULTI_COLOR
};

#endif /* BONUS_H_ */
