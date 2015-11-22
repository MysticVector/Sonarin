#include "PhysicsSystem.h"

#include <iostream>

USING_NS_CC;

PhysicsSystem* PhysicsSystem::create(cocos2d::Node* owner)
{
	PhysicsSystem * ret = new (std::nothrow) PhysicsSystem();
	if (ret != nullptr && ret->init(owner))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void PhysicsSystem::update(float dt)
{
	
}