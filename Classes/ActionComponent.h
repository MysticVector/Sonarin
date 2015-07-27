#ifndef __ACTION_COMPONENT_H__
#define __ACTION_COMPONENT_H__

#include "cocos2d.h"

class ActionComponent : public cocos2d::Component
{
	friend class KeyboardInputSystem;

public:
	ActionComponent()
	{
		_name = "Action";
		_enabled = false;
	}

	virtual ~ActionComponent() {}

	bool _enabled;
};

#endif // __ACTION_COMPONENT_H__