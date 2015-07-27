#ifndef __JUMP_ACTION_COMPONENT_H__
#define __JUMP_ACTION_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class JumpActionComponent : public ActionComponent
{
	friend class KeyboardInputSystem;

public:
	JumpActionComponent()
	{
		_name = "JumpAction";
		_jumping = false;
		_jumpKeyDown = false;
	}

	virtual ~JumpActionComponent() {}

	virtual bool init(float startSpeed)
	{
		_jumpStartSpeedY = startSpeed;
		return true;
	}

	// The amount of upward force to apply when on a jump
	float _jumpStartSpeedY;

	// True is currently jumping, used to prevent jumping in mid-air
	bool _jumping;

	// True if the jump key is currently held down (key must be released to allow a new jump)
	bool _jumpKeyDown;
};

#endif // __JUMP_ACTION_COMPONENT_H__