#include "PhysicsSystem.h"

#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "MoveLeftActionComponent.h"
#include "MoveRightActionComponent.h"

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
	VelocityComponent* velocity = nullptr;
	PhysicsComponent* physics = nullptr;

	MoveLeftActionComponent* moveLeftAction = nullptr;
	MoveRightActionComponent* moveRightAction = nullptr;

	Vector<Node*> entities = _owner->getChildren();

	for (Node* entity : entities)
	{
		if ( (velocity = static_cast<VelocityComponent*>(entity->getComponent("Velocity"))) &&
			 (physics = static_cast<PhysicsComponent*>(entity->getComponent("Physics"))) )
		{
			// Apply deceleration
			// only when no movement action or if both directions are performed
			if ((moveLeftAction = static_cast<MoveLeftActionComponent*>(entity->getComponent("MoveLeftAction")))
				&& (moveRightAction = static_cast<MoveRightActionComponent*>(entity->getComponent("MoveRightAction")))
				&& ((moveLeftAction->isActive() && moveRightAction->isActive()) || (!moveLeftAction->isActive() && !moveRightAction->isActive())) )
			{
				if (velocity->getSpeed().x < 0)
					velocity->getSpeed().x += physics->getDecX() * dt;

				if (velocity->getSpeed().x > 0)
					velocity->getSpeed().x -= physics->getDecX() * dt;

				// Deceleration may produce a speed that is greater than zero but
				// smaller than the smallest unit of deceleration. These lines ensure
				// that the player does not keep travelling at slow speed forever after
				// decelerating.
				if (abs(velocity->getSpeed().x) > 0 &&
					abs(velocity->getSpeed().x) < physics->getDecX() * dt)
					velocity->getSpeed().x = 0;
			}

			// Apply min and max limits to the horizontal velocity
			if (velocity->getSpeed().x < -physics->getMaxSpeed().x)
				velocity->getSpeed().x = -physics->getMaxSpeed().x;

			if (velocity->getSpeed().x > physics->getMaxSpeed().x)
				velocity->getSpeed().x = physics->getMaxSpeed().x;

			// Apply the force of gravity
			velocity->getSpeed().y -= physics->getGravity() * dt;

			// Limit the force of gravity (terminal velocity)
			if (velocity->getSpeed().y < -physics->getMaxSpeed().y)
				velocity->getSpeed().y = -physics->getMaxSpeed().y;
		}
	}
}