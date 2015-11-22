#include "ActionSystem.h"

#include "GameEntity.h"
#include "KeyboardInputComponent.h"
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
			bool moveRequest = false;

			if (moveLeftAction = static_cast<MoveLeftActionComponent*>(entity->getComponent("MoveLeftAction")))
			{
				if (moveLeftAction->isEnabled() && moveLeftAction->isActive())
				{
					velocity->_speed.x -= moveLeftAction->getAcc() * dt;
					moveRequest = true;
				}
			}

			if (moveRightAction = static_cast<MoveRightActionComponent*>(entity->getComponent("MoveRightAction")))
			{
				if (moveRightAction->isEnabled() && moveRightAction->isActive())
				{
					velocity->_speed.x += moveRightAction->getAcc() * dt;
					moveRequest = !moveRequest;
				}
			}
			
			if (jumpAction = static_cast<JumpActionComponent*>(entity->getComponent("JumpAction")))
			{
				if (jumpAction->isEnabled() && jumpAction->isActive() && !jumpAction->isJumping() && !jumpAction->isJumpKeyDown())
				{
					jumpAction->setJumping(true);
					jumpAction->setJumpKeyDown(true);
					velocity->_speed.y = jumpAction->getJumpStartSpeedY();
				}
				else if (!jumpAction->isActive())
				{
					jumpAction->setJumpKeyDown(false);
				}
			}
			
			if (physics = static_cast<PhysicsComponent*>(entity->getComponent("Physics")))
			{
				// Apply deceleration
				if (!moveRequest)
				{
					if (velocity->_speed.x < 0)
						velocity->_speed.x += physics->_decX * dt;

					if (velocity->_speed.x > 0)
						velocity->_speed.x -= physics->_decX * dt;

					// Deceleration may produce a speed that is greater than zero but
					// smaller than the smallest unit of deceleration. These lines ensure
					// that the player does not keep travelling at slow speed forever after
					// decelerating.
					if (abs(velocity->_speed.x) > 0 && 
						abs(velocity->_speed.x) < physics->_decX * dt)
						velocity->_speed.x = 0;
				}

				// Apply the force of gravity
				velocity->_speed.y -= physics->_gravity * dt;

				// Apply min and max limits to the velocity
				if (velocity->_speed.x < -physics->_maxSpeed.x)
					velocity->_speed.x = -physics->_maxSpeed.x;

				if (velocity->_speed.x > physics->_maxSpeed.x)
					velocity->_speed.x = physics->_maxSpeed.x;

				// Limit the force of gravity (terminal velocity)
				if (velocity->_speed.y < -physics->_maxSpeed.y)
					velocity->_speed.y = -physics->_maxSpeed.y;
			}
			
			// Apply final velocity to the desired position
			transform->_pos += velocity->_speed * dt;

			// DEBUG - temporary ground level to stop the player from falling
			if (transform->_pos.y < 256)
			{
				transform->_pos.y = 256;
				jumpAction->setJumping(false);
			}

			// Assign the position of the entity's node from the transform component
			entity->setPosition(transform->_pos);
		}
	}
}