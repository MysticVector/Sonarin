#include "TransformSystem.h"

#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "JumpActionComponent.h"

#include <iostream>

USING_NS_CC;

TransformSystem* TransformSystem::create(cocos2d::Node* owner)
{
	TransformSystem * ret = new (std::nothrow) TransformSystem();
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

void TransformSystem::update(float dt)
{
	TransformComponent* transform = nullptr;
	VelocityComponent* velocity = nullptr;
	JumpActionComponent* jumpAction = nullptr;

	Vector<Node*> entities = _owner->getChildren();

	for (Node* entity : entities)
	{
		if (transform = static_cast<TransformComponent*>(entity->getComponent("Transform")))
		{
			if (velocity = static_cast<VelocityComponent*>(entity->getComponent("Velocity")))
			{
				// Apply final velocity to the desired position
				transform->setNextPosition(transform->getNextPosition() + velocity->getSpeed() * dt);

				// DEBUG - temporary ground level to stop the player from falling
				if (transform->getNextPosition().y < 192)
				{
					transform->getNextPosition().y = 192;

					if (jumpAction = static_cast<JumpActionComponent*>(entity->getComponent("JumpAction")))
					{
						jumpAction->setJumping(false);
					}
				}
			}

			// Assign the position of the entity's node from the transform component
			transform->commitPosition();
		}
	}
}