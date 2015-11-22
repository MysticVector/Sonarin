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

private:
	cocos2d::Vector<cocos2d::Vec2> _points;
};

#endif // __POLYGON_BODY_COMPONENT_H__