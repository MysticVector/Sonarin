#ifndef __MOVECOMMAND_H__
#define __MOVECOMMAND_H__

#include "cocos2d.h"
#include "Command.h"
#include "GameObject.h"

class MoveCommand : public Command
{
public:
	CC_SYNTHESIZE(cocos2d::Vec2, _velocity, Velocity);

	MoveCommand() : _velocity(cocos2d::Vec2::ZERO) {}
	MoveCommand(cocos2d::Vec2 v) : _velocity(v) {}

	virtual void execute(GameObject* object)
	{
		object->move(_velocity);
	}

	virtual ~MoveCommand()	{}
};

#endif // __MOVECOMMAND_H__
