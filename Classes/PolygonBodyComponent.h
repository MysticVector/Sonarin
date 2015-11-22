#ifndef __POLYGON_BODY_COMPONENT_H__
#define __POLYGON_BODY_COMPONENT_H__

#include "cocos2d.h"

class PolygonBodyComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(PolygonBodyComponent);

	virtual bool init()
	{
		_name = "PolygonBody";
		return true;
	}

	void addPoint(cocos2d::Vec2 p) { _points.push_back(p); }
	void removePoint(int i) { _points.erase(_points.begin() + i); }
	cocos2d::Vec2 getPoint(int i) const { return _points.at(i); }

private:
	std::vector<cocos2d::Vec2> _points;
};

#endif // __POLYGON_BODY_COMPONENT_H__