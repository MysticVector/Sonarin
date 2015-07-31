#ifndef __VELOCITY_COMPONENT_H__
#define __VELOCITY_COMPONENT_H__

#include "cocos2d.h"

class VelocityComponent : public cocos2d::Component
{
public:
	VelocityComponent()
	{
		_name = "Velocity";
		_speed = cocos2d::Vec2::ZERO;
	}

	virtual ~VelocityComponent() {}

	// The X,Y movement to occur on the next frame
	cocos2d::Vec2 _speed;
};

#endif // __VELOCITY_COMPONENT_H__