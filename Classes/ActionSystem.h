#ifndef __ACTION_SYSTEM_H__
#define __ACTION_SYSTEM_H__

#include "cocos2d.h"
#include "ScreenLog.h"

class ActionSystem : public cocos2d::Ref
{
public:
	static ActionSystem* create(cocos2d::Node* owner);

	virtual bool init(cocos2d::Node* owner)
	{
		logMsg = g_screenLog->log(LL_DEBUG, "");

		_owner = owner;
		return true;
	}

	void update(float dt);

private:
	// The parent scene where all entities can be accessed
	cocos2d::Node* _owner;

	screenLogMessage* logMsg;
};

#endif // __ACTION_SYSTEM_H__