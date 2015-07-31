#ifndef __VELOCITY_COMPONENT_H__
#define __VELOCITY_COMPONENT_H__

#include "cocos2d.h"

class VelocityComponent : public cocos2d::Component
{
	friend class ActionSystem;
public:
	CREATE_FUNC(VelocityComponent);

	virtual bool init()
	{
		_name = "Velocity";
		_speed = cocos2d::Vec2(0, 0);
		return true;
	}

	// The X,Y movement to occur on the next frame
	CC_SYNTHESIZE(cocos2d::Vec2, _speed, Speed);
};

#endif // __VELOCITY_COMPONENT_H__