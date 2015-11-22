#include "ActionSystem.h"

#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "MoveLeftActionComponent.h"
#include "MoveRightActionComponent.h"
#include "JumpActionComponent.h"

#include <iostream>

USING_NS_CC;

ActionSystem* ActionSystem::create(cocos2d::Node* owner)
{
	ActionSystem * ret = new (std::nothrow) ActionSystem();
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

void ActionSystem::update(float dt)
{
	TransformComponent* transform = nullptr;
	VelocityComponent* velocity = nullptr;
	PhysicsComponent* physics = nullptr;

	MoveLeftActionComponent* moveLeftAction = nullptr;
	MoveRightActionComponent* moveRightAction = nullptr;
	JumpActionComponent* jumpAction = nullptr;

	Vector<Node*> entities = _owner->getChildren();
	
	for (Node* entity : entities)
	{
		if ((transform = static_cast<TransformComponent*>(entity->getComponent("Transform"))) &&
			(velocity = static_cast<VelocityComponent*>(entity->getComponent("Velocity"))))
		{
			if (moveLeftAction = static_cast<MoveLeftActionComponent*>(entity->getComponent("MoveLeftAction")))
			{
				if (moveLeftAction->isEnabled() && moveLeftAction->isActive())
				{
					velocity->getSpeed().x -= moveLeftAction->getAcc() * dt;
				}
			}

			if (moveRightAction = static_cast<MoveRightActionComponent*>(entity->getComponent("MoveRightAction")))
			{
				if (moveRightAction->isEnabled() && moveRightAction->isActive())
				{
					velocity->getSpeed().x += moveRightAction->getAcc() * dt;
				}
			}
			
			if (jumpAction = static_cast<JumpActionComponent*>(entity->getComponent("JumpAction")))
			{
				if (jumpAction->isEnabled() && jumpAction->isActive() && !jumpAction->isJumping() && !jumpAction->isJumpKeyDown())
				{
					jumpAction->setJumping(true);
					jumpAction->setJumpKeyDown(true);
					velocity->getSpeed().y = jumpAction->getJumpStartSpeedY();
				}
				else if (!jumpAction->isActive())
				{
					jumpAction->setJumpKeyDown(false);
				}
			}
		}
	}
}