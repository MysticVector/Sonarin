#ifndef __POLYGON_BODY_COMPONENT_H__
#define __POLYGON_BODY_COMPONENT_H__

#include "cocos2d.h"
#include "BodyComponent.h"

class PolygonBodyComponent : public BodyComponent
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


		cocos2d::log("initialised: (%f,%f) (%f,%f) (%f,%f)", _points[0].x, _points[0].y, _points[1].x, _points[1].y, _points[2].x, _points[2].y);
		CC_SAFE_RELEASE(_polygonShape);
		//cocos2d::PhysicsBody* b = cocos2d::PhysicsBody::createPolygon(_points, _pointsCount);
		//_polygonShape = cocos2d::PhysicsShapePolygon::create(_points, _pointsCount);
		CC_SAFE_RETAIN(_polygonShape);
	}

	cocos2d::Vec2* getPoints() { return _points; }

	virtual bool containsPoint(cocos2d::Vec2 p) { return _polygonShape?(_polygonShape->containsPoint(p)):false; }

	CC_SYNTHESIZE(int, _pointsCount, PointsCount);

protected:
	cocos2d::Vec2* _points;
	cocos2d::PhysicsShapePolygon* _polygonShape;
};

#endif // __POLYGON_BODY_COMPONENT_H__