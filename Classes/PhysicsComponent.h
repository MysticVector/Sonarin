#ifndef __PHYSICS_COMPONENT_H__
#define __PHYSICS_COMPONENT_H__

#include "cocos2d.h"

class PhysicsComponent : public cocos2d::Component
{
public:
	PhysicsComponent() { _name = "Physics"; }

	virtual ~PhysicsComponent() {}

	virtual bool init(cocos2d::Vec2 ms, float g, float d)
	{
		_maxSpeed = ms;
		_gravity = g;
		_decX = d;
		return true;
	}

	// The max movement speed allowed
	cocos2d::Vec2 _maxSpeed;

	// The amount of acceleration to apply
	float _gravity;

	// The amount of deceleration to apply when moving horizontally
	float _decX;
};

#endif // __MOVEMENT_COMPONENT_H__