#ifndef __POLY_LINE_BODY_COMPONENT_H__
#define __POLY_LINE_BODY_COMPONENT_H__

#include "cocos2d.h"

class PolyLineBodyComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(PolyLineBodyComponent);

	virtual bool init()
	{
		_name = "PolyLineBody";
		return true;
	}

	void addLine(cocos2d::Vec2 p1, cocos2d::Vec2 p2)
	{
		_points.push_back(p1);
		_points.push_back(p2);
	}

	void removeLine(int i)
	{
		// Remove the 2 points starting from the i position
		_points.erase(_points.begin() + i);
		_points.erase(_points.begin() + i);
	}

	cocos2d::Vec2 getPoint(int i) const { return _points.at(i); }

	const std::vector<cocos2d::Vec2>& getPoints() const { return _points; }

	// TODO
	virtual bool containsPoint(cocos2d::Vec2 p) { return true; };

protected:
	std::vector<cocos2d::Vec2> _points;
};

#endif // __POLY_LINE_BODY_COMPONENT_H__