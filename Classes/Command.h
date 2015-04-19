#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "cocos2d.h"

class GameObject;

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameObject* object) = 0;
};

#endif // __COMMAND_H__
