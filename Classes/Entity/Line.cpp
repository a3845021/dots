#include "Line.h"

Line* Line::create(const CCPoint& start, const CCPoint& end,
		const ccColor4F& color) {
	auto line = new Line();
	if (line) {
		line->init(start, end, color);
		line->autorelease();
	}
	return line;
}

Line::~Line() {
}

void Line::init(const CCPoint& start, const CCPoint& end,
		const ccColor4F& color) {
	CCDrawNode::init();
	this->start = start;
	this->end = end;
	this->color = color;
	drawSegment(start, end, WIDTH, color);
}
