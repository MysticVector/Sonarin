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

	void setActive(bool active) { _active = active; }
	bool isActive() const { return _active; }
protected:

	// Whether the action is being performed
	bool _active;
};

#endif // __ACTION_COMPONENT_H__