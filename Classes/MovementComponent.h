#ifndef __MOVEMENT_COMPONENT_H__
#define __MOVEMENT_COMPONENT_H__

#include "cocos2d.h"

class MovementComponent : public cocos2d::Component
{
public:
	MovementComponent() { _name = "Movement";	}

	virtual bool init(const cocos2d::Vec2& speed, 
		const cocos2d::Vec2& maxSpeed,
		const cocos2d::Vec2& acc,
		float decX,
		float jumpStartSpeedY);

	virtual ~MovementComponent() {}

	// The X,Y movement to occur on the next frame
	cocos2d::Vec2 speed;

	// The max movement speed allowed
	cocos2d::Vec2 maxSpeed;

	// The amount of acceleration to apply
	cocos2d::Vec2 acc;

	// The amount of deceleration to apply when moving horizontally
	float decX;

	// The amount of upward force to apply when on a jump
	float jumpStartSpeedY;

	// True is currently jumping, used to prevent jumping in mid-air
	bool jumping;

	// True if the jump key is currently held down (key must be released to allow a new jump)
	bool jumpKeyDown;
};

#endif // __MOVEMENT_COMPONENT_H__