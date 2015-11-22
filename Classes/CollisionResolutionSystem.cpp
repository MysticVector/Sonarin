#include "CollisionResolutionSystem.h"

#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "JumpActionComponent.h"

#include <iostream>

USING_NS_CC;

CollisionResolutionSystem* CollisionResolutionSystem::create(cocos2d::Node* owner)
{
	CollisionResolutionSystem * ret = new (std::nothrow) CollisionResolutionSystem();
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

void CollisionResolutionSystem::update(float dt)
{
	TransformComponent* transform = nullptr;
	VelocityComponent* velocity = nullptr;
	JumpActionComponent* jumpAction = nullptr;

	Vector<Node*> entities = _owner->getChildren();

	for (Node* entity : entities)
	{

	}
}