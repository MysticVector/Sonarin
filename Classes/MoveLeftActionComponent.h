#ifndef __MOVE_LEFT_ACTION_COMPONENT_H__
#define __MOVE_LEFT_ACTION_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class MoveLeftActionComponent : public ActionComponent
{
public:
	CREATE_FUNC(MoveLeftActionComponent);

	virtual bool init()
	{
		_name = "MoveLeftAction";
		_acc = 0;
		return true;
	}

	// The amount of acceleration to apply
	CC_SYNTHESIZE(float, _acc, Acc);
};

#endif // __MOVE_LEFT_ACTION_COMPONENT_H__