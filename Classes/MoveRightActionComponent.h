#ifndef __MOVE_RIGHT_ACTION_COMPONENT_H__
#define __MOVE_RIGHT_ACTION_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class MoveRightActionComponent : public ActionComponent
{
public:
	CREATE_FUNC(MoveRightActionComponent);

	virtual bool init()
	{
		_name = "MoveRightAction";
		_acc = 0;
		return true;
	}

	// The amount of acceleration to apply
	CC_SYNTHESIZE(float, _acc, Acc);
};

#endif // __MOVE_RIGHT_ACTION_COMPONENT_H__