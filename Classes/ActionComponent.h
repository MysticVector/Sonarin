#ifndef __ACTION_COMPONENT_H__
#define __ACTION_COMPONENT_H__

#include "cocos2d.h"

class ActionComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(ActionComponent);

	virtual bool init()
	{
		_name = "Action";
		_enabled = false;
		return true;
	}

	bool _enabled;
};

#endif // __ACTION_COMPONENT_H__