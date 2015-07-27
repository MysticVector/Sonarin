#ifndef __MOVE_LEFT_ACTION_COMPONENT_H__
#define __MOVE_LEFT_ACTION_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class MoveLeftActionComponent : public ActionComponent
{
public:
	MoveLeftActionComponent() {	_name = "MoveLeftAction"; }

	virtual ~MoveLeftActionComponent() {}

	virtual bool init(float a)
	{
		_acc = a;
		return true;
	}

	// The amount of acceleration to apply
	float _acc;
};

#endif // __MOVE_LEFT_ACTION_COMPONENT_H__