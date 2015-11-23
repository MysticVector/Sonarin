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

	void addPoint(cocos2d::Vec2 p) { _points.push_back(p); }
	void removePoint(int i) { _points.erase(_points.begin() + i); }
	cocos2d::Vec2 getPoint(int i) const { return _points.at(i); }

	const std::vector<cocos2d::Vec2>& getPoints() const { return _points; }

private:
	std::vector<cocos2d::Vec2> _points;
};

#endif // __POLY_LINE_BODY_COMPONENT_H__