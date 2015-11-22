#ifndef __PHYSICS_COMPONENT_H__
#define __PHYSICS_COMPONENT_H__

#include "cocos2d.h"

class PhysicsComponent : public cocos2d::Component
{
	friend class ActionSystem;
public:
	CREATE_FUNC(PhysicsComponent);

	virtual bool init()
	{
		_name = "Physics";
		_maxSpeed = cocos2d::Vec2::ZERO;
		_gravity = 0;
		_decX = 0;
		return true;
	}

	// The max movement speed allowed
	CC_SYNTHESIZE(cocos2d::Vec2, _maxSpeed, MaxSpeed);

	// The amount of acceleration to apply
	CC_SYNTHESIZE(float, _gravity, Gravity);

	// The amount of deceleration to apply when moving horizontally
	CC_SYNTHESIZE(float, _decX, DecX);
};

#endif // __PHYSICS_COMPONENT_H__