#ifndef __POLYGON_BODY_COMPONENT_H__
#define __POLYGON_BODY_COMPONENT_H__

#include "cocos2d.h"

class PolygonBodyComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(PolygonBodyComponent);

	virtual ~PolygonBodyComponent()
	{
		CC_SAFE_RELEASE(_polygonShape);
		CC_SAFE_DELETE_ARRAY(_points);
	}

	virtual bool init()
	{
		_name = "PolygonBody";
		_polygonShape = nullptr;
		return true;
	}

	void setPoints(cocos2d::Vec2* points, int pointsCount)
	{
		_points = points;
		_pointsCount = pointsCount;


		CC_SAFE_RELEASE(_polygonShape);
		_polygonShape = cocos2d::PhysicsShapePolygon::create(_points, _pointsCount);
		CC_SAFE_RETAIN(_polygonShape);
	}

	cocos2d::Vec2* getPoints() { return _points; }

	CC_SYNTHESIZE(int, _pointsCount, PointsCount);

protected:
	cocos2d::Vec2* _points;
	cocos2d::PhysicsShapePolygon* _polygonShape;
};

#endif // __POLYGON_BODY_COMPONENT_H__