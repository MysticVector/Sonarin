#ifndef __JUMP_ACTION_COMPONENT_H__
#define __JUMP_ACTION_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class JumpActionComponent : public ActionComponent
{
	friend class ActionSystem;
public:
	CREATE_FUNC(JumpActionComponent);

	virtual bool init()
	{
		_name = "JumpAction";
		_jumpStartSpeedY = 0;
		_jumping = false;
		_jumpKeyDown = false;
		return true;
	}

	
	// The amount of upward force to apply when on a jump
	CC_SYNTHESIZE(float, _jumpStartSpeedY, JumpStartSpeedY);

	// True is currently jumping, used to prevent jumping in mid-air
	CC_SYNTHESIZE(bool, _jumping, Jumping);

	// True if the jump key is currently held down (key must be released to allow a new jump)
	CC_SYNTHESIZE(bool, _jumpKeyDown, JumpKeyDown);
};

#endif // __JUMP_ACTION_COMPONENT_H__