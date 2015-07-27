#ifndef __MOVE_RIGHT_ACTION_COMPONENT_H__
#define __MOVE_RIGHT_ACTION_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class MoveRightActionComponent : public ActionComponent
{
public:
	MoveRightActionComponent() { _name = "MoveRightAction"; }

	virtual ~MoveRightActionComponent() {}

	virtual bool init(float a)
	{
		_acc = a;
		return true;
	}

	// The amount of acceleration to apply
	float _acc;
};

#endif // __MOVE_RIGHT_ACTION_COMPONENT_H__