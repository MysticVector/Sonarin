#ifndef __COLLISION_RESOLUTION_SYSTEM_H__
#define __COLLISION_RESOLUTION_SYSTEM_H__

#include "cocos2d.h"
#include "BoxBodyComponent.h"

class CollisionResolutionSystem : public cocos2d::Ref
{
public:
	static CollisionResolutionSystem* create(cocos2d::Node* owner);

	virtual bool init(cocos2d::Node* owner)
	{
		_owner = owner;
		return true;
	}

	void initAABBs();

	void update(float dt);

private:
	// The parent scene where all entities can be accessed
	cocos2d::Node* _owner;
};

#endif // __COLLISION_RESOLUTION_SYSTEM_H__