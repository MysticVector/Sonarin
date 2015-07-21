#include "MovementSystem.h"

#include "GameEntity.h"
#include "InputComponent.h"
#include "TranformComponent.h"
#include "MovementComponent.h"
#include <iostream>

USING_NS_CC;

void MovementSystem::registerEntity(GameEntity* e)
{
	_entities.pushBack(e);
}

void MovementSystem::unregisterEntity(GameEntity* e)
{
	_entities.eraseObject(e, true);
}

void MovementSystem::update(float dt)
{
	TransformComponent* transform = nullptr;
	MovementComponent* movement = nullptr;
	InputComponent* input = nullptr;

	for (GameEntity* entity : _entities)
	{
		if ((transform = static_cast<TransformComponent*>(entity->getComponent("Transform"))) &&
			(movement = static_cast<MovementComponent*>(entity->getComponent("Movement"))))
		{
			bool moveRequest = false;

			if (input = static_cast<InputComponent*>(entity->getComponent("Input")))
			{					
				// Check for input from the player
				if (input->isActionPressed(InputAction::MoveRight))
				{
					movement->speed.x += movement->acc.x * dt;
					moveRequest = !moveRequest;
				}
				if (input->isActionPressed(InputAction::MoveLeft))
				{
					movement->speed.x -= movement->acc.x * dt;
					moveRequest = !moveRequest;
				}
			}

			if (input->isActionPressed(InputAction::Jump) && !movement->jumping && !movement->jumpKeyDown)
			{
				movement->jumping = true;
				movement->jumpKeyDown = true;
				movement->speed.y = movement->jumpStartSpeedY;
			}
			else if (!input->isActionPressed(InputAction::Jump))
			{
				movement->jumpKeyDown = false;
			}

			// Apply deceleration
			if (!moveRequest)
			{
				if (movement->speed.x > 0)
					movement->speed.x -= movement->decX * dt;

				if (movement->speed.x < 0)
					movement->speed.x += movement->decX * dt;

				// Deceleration may produce a speed that is greater than zero but
				// smaller than the smallest unit of deceleration. These lines ensure
				// that the player does not keep travelling at slow speed forever after
				// decelerating.
				if (abs(movement->speed.x) > 0 && 
					abs(movement->speed.x) < movement->decX * dt)
					movement->speed.x = 0;
			}

			// Apply the force of gravity
			movement->speed.y -= movement->acc.y;

			std::cout << movement->speed.y << std::endl;

			// Apply min and max limits to the velocity
			if (movement->speed.x > movement->maxSpeed.x)
				movement->speed.x = movement->maxSpeed.x;
			
			if (movement->speed.x < -movement->maxSpeed.x)
				movement->speed.x = -movement->maxSpeed.x;

			// Limit the force of gravity (terminal velocity)
			if (movement->speed.y < -movement->maxSpeed.y)
				movement->speed.y = -movement->maxSpeed.y;

			
			// Apply final velocity to the desired position
			transform->pos += movement->speed * dt;

			// DEBUG - temporary ground level to stop the player from falling
			if (transform->pos.y < 256)
			{
				transform->pos.y = 256;
				movement->jumping = false;
			}

			// Assign the position of the entity's node from the transform component
			entity->setPosition(transform->pos);
		}
	}
}