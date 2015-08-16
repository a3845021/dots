#ifndef LINE_H_
#define LINE_H_

#include "cocos2d.h"
#include "../Constants.h"
USING_NS_CC;

class Line: public CCDrawNode {
public:

	static constexpr float WIDTH = 3.0f;

	static Line* create(const CCPoint& start, const CCPoint& end,
			const ccColor4F& color);

	virtual ~Line();

private:

	CCPoint start, end;
	ccColor4F color;

	void init(const CCPoint& start, const CCPoint& end, const ccColor4F& color);
};

#endif /* LINE_H_ */
