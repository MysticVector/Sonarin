#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

#include "cocos2d.h"

class PhysicsSystem : public cocos2d::Ref
{
public:
	static PhysicsSystem* create(cocos2d::Node* owner);

	virtual bool init(cocos2d::Node* owner)
	{
		_owner = owner;
		return true;
	}

	void update(float dt);

private:
	// The parent scene where all entities can be accessed
	cocos2d::Node* _owner;
};

#endif // __PHYSICS_SYSTEM_H__