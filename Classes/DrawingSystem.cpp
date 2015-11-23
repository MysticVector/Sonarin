#include "DrawingSystem.h"

#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "JumpActionComponent.h"
#include "SpriteComponent.h"
#include "DebugNodeComponent.h"
#include "PolyLineBodyComponent.h"

#include <iostream>

USING_NS_CC;

DrawingSystem* DrawingSystem::create(cocos2d::Node* owner)
{
	DrawingSystem * ret = new (std::nothrow) DrawingSystem();
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

void DrawingSystem::draw()
{
	DebugNodeComponent* debugNode = nullptr;
	PolyLineBodyComponent* polyLineBody = nullptr;
	SpriteComponent* sprite = nullptr;
	TransformComponent* transform = nullptr;

	Vector<Node*> entities = _owner->getChildren();

	for (Node* entity : entities)
	{

		if (transform = static_cast<TransformComponent*>(entity->getComponent("Transform")))
		{
			// Drawing the debug boxes/lines/points
			if (debugNode = static_cast<DebugNodeComponent*>(entity->getComponent("DebugNode")))
			{
				// Depending on what type of entity we have make the right calls
				if (polyLineBody = static_cast<PolyLineBodyComponent*>(entity->getComponent("PolyLineBody")))
				{
					debugNode->drawLines(polyLineBody->getPoints());
				}
				else if (sprite = static_cast<SpriteComponent*>(entity->getComponent("Sprite")))
				{
					debugNode->drawRect(Rect(transform->getNextPosition(), sprite->getSprite()->getContentSize()));
				}
				else
				{
					debugNode->drawPoint(transform->getNextPosition());
				}
			}
		}
	}
}