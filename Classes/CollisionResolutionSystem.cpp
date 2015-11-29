#include "CollisionResolutionSystem.h"

#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "PolyLineBodyComponent.h"
#include "PhysicsComponent.h"
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
	PhysicsComponent* physics = nullptr;
	PolyLineBodyComponent* polyLineBody = nullptr;
	JumpActionComponent* jumpAction = nullptr;
	
	Vector<Node*> entities = _owner->getChildren();

	for (Node* entity : entities)
	{
		if ((transform = static_cast<TransformComponent*>(entity->getComponent("Transform")))
			&& (physics = static_cast<PhysicsComponent*>(entity->getComponent("Physics")))
			&& (polyLineBody = static_cast<PolyLineBodyComponent*>(entity->getComponent("PolyLineBody"))))
		{
			// Flags to specify what kind of collision has occurred
			bool contactX = true, contactYbottom = true, contactYtop = true;

			// Keep iterating the contact solver until the maximum number of iterations is reached
			// or no collisions are detected
			for (int iteration = 0; iteration < PhysicsComponent::iterations && (contactX || contactYbottom || contactYtop); iteration++)
			{
				// Calculate the amount of X and Y movement expected by the player this frame
				float nextMoveX = transform->getNextPosition().x * dt;
				float nextMoveY = transform->getNextPosition().y * dt;

				// No collisions found yet
				contactX = contactYbottom = contactYtop = false;

				float projectedMoveX, projectedMoveY, originalMoveX, originalMoveY;

				// Store the original final expected movement of the player so we can
				// see if it has been modified due to a collision or potential collision later
				originalMoveX = nextMoveX;
				originalMoveY = nextMoveY;

				// Iterate over each object whose bounding box intersects with the player's bounding box
				// until a collision is found
				BodyComponent* objectBody = nullptr;
				Vector<Node*> entities = _owner->getChildren();

				//for (int i = 0; i < entities.size() && !contactX && !contactYbottom && !contactYtop; i++)
				//{
				//	// Select only physics body objects
				//	if ((objectBody = static_cast<BodyComponent*>(entities.at(i)->getComponent("BoxBody"))) ||
				//		(objectBody = static_cast<BodyComponent*>(entities.at(i)->getComponent("PolygonBody"))))
				//	{
				//		while ((objectBody->containsPoint(Vec2(static_cast(polyLineBody->getPoints().at(dir * 2).x + playerX + projectedMoveX),
				//			static_cast(collisionPoint[dir * 2].y + playerY + projectedMoveY))
				//			|| worldObjects[o].ContainsPoint(static_cast(collisionPoint[dir * 2 + 1].x + playerX + projectedMoveX),
				//				static_cast(collisionPoint[dir * 2 + 1].y + playerY + projectedMoveY))))
				//		{
				//			if (dir == 0) projectedMoveY++;
				//			if (dir == 1) projectedMoveY--;
				//			if (dir == 2) projectedMoveX++;
				//			if (dir == 3) projectedMoveX--;
				//		}

				//	}
				//}

			}
		}
	}
}