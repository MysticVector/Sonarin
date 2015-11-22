#ifndef __VELOCITY_COMPONENT_H__
#define __VELOCITY_COMPONENT_H__

#include "cocos2d.h"

class VelocityComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(VelocityComponent);

	virtual bool init()
	{
		_name = "Velocity";
		_speed = cocos2d::Vec2(0, 0);
		return true;
	}

	void setSpeed(cocos2d::Vec2 speed) { _speed = speed; }
	cocos2d::Vec2& getSpeed() { return _speed; }
protected:

	// The X,Y movement to occur on the next frame
	cocos2d::Vec2 _speed;
};

#endif // __VELOCITY_COMPONENT_H__