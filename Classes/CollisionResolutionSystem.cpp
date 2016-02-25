#include "CollisionResolutionSystem.h"

#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "PolyLineBodyComponent.h"
#include "PhysicsComponent.h"
#include "JumpActionComponent.h"
#include "BoxBodyComponent.h"

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

void CollisionResolutionSystem::initAABBs()
{
	BoxBodyComponent* objectBody = nullptr;
	DrawNode* drawNode = DrawNode::create();

	Vector<Node*> entities = _owner->getChildren();
	for (Node* entity : entities)
	{
		// Select only physics body objects
		if ((objectBody = static_cast<BoxBodyComponent*>(entity->getComponent("BoxBody"))) && objectBody->getRotation() != 0)
		{
			drawNode->clear();

			// Changing the content size to take the anchor into consideration
			drawNode->setContentSize(objectBody->getRect().size);

			// Anchor at the top left of the rectangle, in order to do a rotation the same way it was done in Tiled Map Editor
			drawNode->setAnchorPoint(cocos2d::Vec2(0, 1));

			// Return the rectangle the same position it had in the Tiled Map Editor
			// (the positions get converted to cocos2d's inverted axis upon loading the TMX file)
			drawNode->setPositionY(objectBody->getRect().origin.y + objectBody->getRect().size.height);

			drawNode->drawRect(objectBody->getRect().origin, objectBody->getRect().origin + objectBody->getRect().size, Color4F::WHITE);
			drawNode->setRotation(objectBody->getRotation());

			objectBody->setAABB(Rect(drawNode->getBoundingBox().origin, drawNode->getBoundingBox().size));
		}
	}

	CC_SAFE_DELETE(drawNode);
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
			&& (velocity = static_cast<VelocityComponent*>(entity->getComponent("Velocity")))
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
				float nextMoveX = velocity->getSpeed().x * dt;
				float nextMoveY = velocity->getSpeed().y * dt;

				// No collisions found yet
				contactX = contactYbottom = contactYtop = false;

				float projectedMoveX, projectedMoveY, originalMoveX, originalMoveY;

				// Store the original final expected movement of the player so we can
				// see if it has been modified due to a collision or potential collision later
				originalMoveX = nextMoveX;
				originalMoveY = nextMoveY;

				// Iterate over each object whose bounding box intersects with the player's bounding box
				// until a collision is found
				BoxBodyComponent* objectBody = nullptr;
				Vector<Node*> entities = _owner->getChildren();

				for (int i = 0; i < entities.size() && !contactX && !contactYbottom && !contactYtop; i++)
				{
					// Select only physics body objects
					if (objectBody = static_cast<BoxBodyComponent*>(entities.at(i)->getComponent("BoxBody")))
					{
						// We will test the four possible directions of player movement individually
						// dir: 0 = top, 1 = bottom, 2 = left, 3 = right
						for (int dir = 0; dir < 4; dir++)
						{
							// Skip the test if the expected direction of movement makes the test irrelevant
							// For example, we only want to test the top of the player's head when movement is
							// upwards, not downwards. This is really important! If we don't do this, we can
							// make corrections in the wrong direction, causing the player to magically jump
							// up to platforms or stick to ceilings.
							if (dir == 0 && nextMoveY < 0) continue;
							if (dir == 1 && nextMoveY > 0) continue;
							if (dir == 2 && nextMoveX > 0) continue;
							if (dir == 3 && nextMoveX < 0) continue;
							projectedMoveX = (dir >= 2 ? nextMoveX : 0);
							projectedMoveY = (dir <  2 ? nextMoveY : 0);

							TransformComponent* t = static_cast<TransformComponent*>(entities.at(i)->getComponent("Transform"));
							Rect worldSpaceRect = Rect(t->getNextPosition() + objectBody->getRect().origin, objectBody->getRect().size);

							// Collision points before the projected movement vector is added
							Vec2 oldP1 = Vec2(polyLineBody->getPoints().at(dir * 2).x + transform->getNextPosition().x,
										polyLineBody->getPoints().at(dir * 2).y + transform->getNextPosition().y);
							Vec2 oldP2 = Vec2(polyLineBody->getPoints().at(dir * 2 + 1).x + transform->getNextPosition().x,
										polyLineBody->getPoints().at(dir * 2 + 1).y + transform->getNextPosition().y);

							while (BoxBodyComponent::containsPoint(worldSpaceRect, oldP1 + Vec2(projectedMoveX, projectedMoveY), objectBody->getRotation())
								|| BoxBodyComponent::containsPoint(worldSpaceRect, oldP2 + Vec2(projectedMoveX, projectedMoveY), objectBody->getRotation()))
							{
								if (dir == 0) projectedMoveY -= dt;
								if (dir == 1) projectedMoveY += dt;
								if (dir == 2) projectedMoveX += dt;
								if (dir == 3) projectedMoveX -= dt;
							}

							if (dir >= 2 && dir <= 3) nextMoveX = projectedMoveX;
							if (dir >= 0 && dir <= 1) nextMoveY = projectedMoveY;

							// Close the for loop (repeat for all four directions)
						}

						// Detect what type of contact has occurred based on a comparison of
						// the original expected movement vector and the new one

						if (nextMoveY < originalMoveY  && originalMoveY >= 0)
						{
							contactYtop = true;
						}

						if (nextMoveY > originalMoveY && originalMoveY <= 0)
						{
							contactYbottom = true;
						}

						if (abs(nextMoveX - originalMoveX) > 0.01f)
						{
							contactX = true;
						}

						// The player can't continue jumping if we hit the side of something, must fall instead
						// Without this, a player hitting a wall during a jump will continue trying to travel
						// upwards
						// CHARNET3D: Feels unnatural, to be retested later
						/*if (contactX && velocity->getSpeed().y > 0)
							velocity->getSpeed().y = nextMoveY = 0;*/
					}
				}

				// If a contact has been detected, apply the re-calculated movement vector
				// and disable any further movement this frame (in either X or Y as appropriate)
				if (contactYbottom || contactYtop)
				{
					transform->getNextPosition().y += nextMoveY;
					velocity->getSpeed().y = 0;

					if (contactYbottom
						&& (jumpAction = static_cast<JumpActionComponent*>(entity->getComponent("JumpAction"))))
					{
						jumpAction->setJumping(false);
					}
				}

				if (contactX)
				{
					transform->getNextPosition().x += nextMoveX;
					velocity->getSpeed().x = 0;
				}
			}
		}
	}
}