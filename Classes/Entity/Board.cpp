#include "Board.h"

Board* Board::create(int rows, int columns) {
	auto board = new Board();
	if (board && board->initWithSize(rows, columns)) {
		board->autorelease();
	} else {
		CC_SAFE_DELETE(board);
	}
	return board;
}

Board::~Board() {
}

void Board::onTouch(Dot* dot, const CCPoint& position) {
	auto state = stateMachine.getCurrentState();
	switch (state) {
	case State::INITIAL:
		stateMachine.changeState(State::CONNECTING);
		connectionDots.insert(dot);
		currentDot = dot;
		break;
	case State::SWAP:
		dot->swapWith(swapDot);
		lightOffAllDots();
		stateMachine.changeState(State::INITIAL);
		for (auto listener : listeners) {
			listener->onDotSwitchComplete();
		}
		break;
	case State::CHANGE_COLOR:
		dot->changeColorWithRandom();
		lightOffAllDots();
		stateMachine.changeState(State::INITIAL);
		for (auto listener : listeners) {
			listener->onDotChangeColorComplete();
		}
		break;
	case State::REMOVE_DOT:
		lightOffAllDots();
		std::set<Dot*> dotsToReplace = { dot };
		replaceDots(dotsToReplace);
		stateMachine.changeState(State::INITIAL);
		for (auto listener : listeners) {
			listener->onDotRemoveComplete();
		}
		break;
	}
}

void Board::changeDotColorWithRandom() {
	lightOnAllDots();
	stateMachine.changeState(State::CHANGE_COLOR);
}

void Board::chooseDotToRemove() {
	lightOnAllDots();
	stateMachine.changeState(State::REMOVE_DOT);
}

void Board::startMultiColorConnect(DotColor c1, DotColor c2) {

	forEachDot([&](Dot* d) {
		if(d->getColor() == c1) {
			d->allowConnectionToColor(c2);
		} else if (d->getColor() == c2) {
			d->allowConnectionToColor(c1);
		}
	});
}

void Board::stopMultiColorConnect() {
	forEachDot([&](Dot* d) {
		d->removeConnectionColors();
	});
}

void Board::addListener(BoardListener* listener) {
	listeners.push_back(listener);
}

void Board::drawBackground() {
	ccDrawSolidRect(VisibleRect::leftTop(), VisibleRect::rightBottom(),
			toColor4F(backgroundColor));
}

void Board::lightOffAllDots() {
	forEachDot([](Dot* d) {
		d->lightOff();
	});
}

void Board::lightOnAllDots() {
	forEachDot([](Dot* d) {
		d->lightOn();
	});
}

void Board::switchDotWith(Dot* dot) {
	lightOnAllDots();
	stateMachine.changeState(State::SWAP);
	swapDot = dot;
}

Dot* Board::findDotAt(const CCPoint& position) {
	Dot* result = nullptr;
	forEachDot([&] (Dot* d) {
		if(d->boundingRect().containsPoint(position)) {
			result = d;
		}
	});
	return result;
}

void Board::onMoveTouch(Dot* dot, const CCPoint& position) {
	if (stateMachine.getCurrentState() == State::CONNECTING) {
		auto newDot = findDotAt(position);
		if (newDot == nullptr) {
			return;
		}
		if (newDot == currentDot) {
			return;
		}
		if (!currentDot->canConnectTo(newDot)) {
			return;
		}
		if (connectionDots.size() == 3 && isInConnection(newDot)) {
			return;
		}

		if (connectionDots.size() == 1) {
			for (auto listener : listeners) {
				listener->onDotSelected(*connectionDots.begin(),
						connectionDots.size());
			}
		}

		for (auto listener : listeners) {
			listener->onDotSelected(newDot, connectionDots.size());
		}
		currentDot->connectTo(newDot);
		newDot->connectTo(currentDot);
		if (isInConnection(newDot)) {
			playSoundEffect("ConnectionComplete");
			lightOnBoard();
			stateMachine.changeState(State::CONNECTED);
		} else {
			connectionDots.insert(newDot);
			std::string effectToPlay = "ConnectDots_6";
			if (connectionDots.size() < 6) {
				effectToPlay = std::string(
						Formatter::toString("ConnectDots_%d",
								connectionDots.size()));
			}
			playSoundEffect(effectToPlay.c_str());
			currentDot = newDot;
		}
	}
}

void Board::onEndTouch(Dot* dot, const CCPoint& position) {
	if (connectionDots.size() <= 1) {

	} else {
		if (stateMachine.getCurrentState() == State::CONNECTING) {
			onConnectingComplete(connectionDots);
		} else if (stateMachine.getCurrentState() == State::CONNECTED) {
			auto outerDots = findOuterDotsUsingBFS();
			std::set<Dot*> dotsToRemove;
			forEachDot([&](Dot* d) {
				dotsToRemove.insert(d);
			});

			for (auto d : outerDots) {
				dotsToRemove.erase(d);
			}
			onConnectionComplete(dotsToRemove);
		}
	}
	stateMachine.changeState(State::INITIAL);
	connectionDots.clear();
}

void Board::addDots() {
	auto director = CCDirector::sharedDirector();
	auto visibleSize = director->getVisibleSize();
	auto dotPadding = 35.0f;
	auto dotDiameter = (visibleSize.width / 20.0f) * 2.0f;
	auto center = VisibleRect::center();
	auto leftPoint = center.x - (3.0f * dotPadding) - (3.0f * dotDiameter)
			- ((dotDiameter + dotPadding) / 2);
	auto topPoint = center.y + (3.0f * dotPadding) + (3.0f * dotDiameter)
			+ ((dotDiameter + dotPadding) / 20);
	dotRadius = visibleSize.width / 28.0f;
	for (int row = 1; row <= rows; row++) {
		for (int column = 1; column <= columns; column++) {
			auto xPos = leftPoint + (column * dotPadding)
					+ (column * dotDiameter);
			auto yPos = topPoint - (row * dotPadding) - (row * dotDiameter);
			auto dot = addDotWithRandomColor(row, column, ccp(xPos, yPos));
			dot->bounce();
		}
	}
	rowDotDistance = ccpDistance(dotAt(1, 1)->getPosition(),
			dotAt(2, 1)->getPosition());
}

bool Board::initWithSize(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	addDots();
	stateMachine.changeState(State::INITIAL);
	backgroundColor = BACKGROUND_COLOR;
	return true;
}

Dot* Board::dotAt(int row, int column) {
	return (Dot*) getChildByTag(tagOf(row, column));
}

bool Board::isInConnection(Dot* dot) {
	return connectionDots.find(dot) != connectionDots.end();
}

std::set<Dot*> Board::findOuterDotsUsingBFS() {
	std::set<Dot*> outerDots;
	bool visited[100] = { false };
	int edgeDots[][2] = { { 1, 1 }, { 1, columns }, { rows, 1 },
			{ rows, columns } };
	for (int i = 0; i < 4; i++) {
		queue<Dot*> q;
		auto startDot = dotAt(edgeDots[i][0], edgeDots[i][1]);
		if (isInConnection(startDot) || visited[startDot->getTag()]) {
			continue;
		}
		visited[startDot->getTag()] = true;
		q.push(startDot);
		while (!q.empty()) {
			auto dot = q.front();
			outerDots.insert(dot);
			q.pop();

			auto neighbors = neighborsOf(dot);
			for (auto neighbor : neighbors) {
				if (!visited[neighbor->getTag()] && !isInConnection(neighbor)) {
					visited[neighbor->getTag()] = true;
					q.push(neighbor);
				}
			}
		}
	}
	return outerDots;
}

std::vector<Dot*> Board::neighborsOf(Dot* dot) {
	std::vector<Dot*> result;
	int row = dot->getRow();
	int column = dot->getColumn();
	if (row - 1 > 0) {
		result.push_back(dotAt(row - 1, column));
	}
	if (row + 1 <= rows) {
		result.push_back(dotAt(row + 1, column));
	}
	if (column - 1 > 0) {
		result.push_back(dotAt(row, column - 1));
	}
	if (column + 1 <= columns) {
		result.push_back(dotAt(row, column + 1));
	}

	return result;
}

int Board::tagOf(int row, int column) {
	return column + (row - 1) * columns;
}

void Board::onConnectingComplete(std::set<Dot*> dotsToRemove) {
	for (auto listener : listeners) {
		listener->onDotsConnected(dotsToRemove.size());
	}
	replaceDots(dotsToRemove);
}

void Board::onConnectionComplete(std::set<Dot*> dotsToRemove) {
	for (auto listener : listeners) {
		listener->onDotsConnectedInConnection(dotsToRemove.size());
	}
	replaceDots(dotsToRemove);
}

float Board::getDotRowDistance() {
	return rowDotDistance;
}

void Board::replaceDots(std::set<Dot*> dotsToReplace) {
	std::map<int, std::vector<Dot*> > dotsToRemoveInColumns;
	for (auto d : dotsToReplace) {
		dotsToRemoveInColumns[d->getColumn()].push_back(d);
	}

	for (auto entry : dotsToRemoveInColumns) {
		auto dots = entry.second;
		auto dotsSize = dots.size();

		std::set<Dot*> dotsInColumn;
		int column = entry.first;
		for (int row = 1; row <= rows; row++) {
			dotsInColumn.insert(dotAt(row, column));
		}

		for (auto d : dots) {
			dotsInColumn.erase(d);
		}

		for (int i = 1; i <= dotsSize; i++) {
			auto topDotPos = dotAt(1, column)->getPosition();
			auto position = ccpAdd(topDotPos, ccp(0.0f, i * getDotRowDistance()));
			auto dot = addDotWithRandomColor(1 - i, column, position);
			dotsInColumn.insert(dot);
		}

		for (auto dot : dotsInColumn) {
			int dotsBelow = 0;
			for (auto d : dots) {
				if (d->getRow() > dot->getRow()) {
					dotsBelow++;
				}
				d->removeFromParentAndCleanup(true);
			}
			float moveY = dotsBelow * getDotRowDistance();
			int newRow = dot->getRow() + dotsBelow;
			dot->setRow(newRow);
			dot->setTag(tagOf(dot->getRow(), dot->getColumn()));
			dot->slideBy(ccp(0.0f, -moveY));
		}
	}
}

Dot* Board::addDotWithRandomColor(int row, int column,
		const CCPoint& position) {
	auto newDot = Dot::createWithRandomColor(dotRadius);
	newDot->setPosition(position);
	newDot->setColumn(column);
	newDot->setRow(row);
	newDot->setTag(tagOf(row, column));
	newDot->setListener(this);
	newDot->allowConnectionToColor(newDot->getColor());
	addChild(newDot);
	return newDot;
}

void Board::lightOnBoard() {
	auto iterator = connectionDots.begin();
	auto dot = *iterator;
	backgroundColor = getColor(dot->getOriginalColor());
	runAction(
			CCSequence::create(CCDelayTime::create(1.0f),
					CCCallFunc::create(this,
							callfunc_selector(Board::lightOffBoard)), NULL));
}

void Board::lightOffBoard() {
	backgroundColor = BACKGROUND_COLOR;
}
