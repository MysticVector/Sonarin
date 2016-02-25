#ifndef __GAMEENTITY_H__
#define __GAMEENTITY_H__

#include "cocos2d.h"
#include "SpriteComponent.h"
#include "TiledMapComponent.h"
#include "DebugNodeComponent.h"

class GameEntity : public cocos2d::Node
{
public:
	CREATE_FUNC(GameEntity);

	virtual bool init()
	{
		_name = "GameEntity";
		return true;
	}

	virtual bool addComponent(cocos2d::Component *component)
	{
		assert(component);
		if (component->getName() == "Sprite")
		{
			SpriteComponent* sc = static_cast<SpriteComponent*>(component);
			assert(sc->getSprite());
			addChild(sc->getSprite());
		}
		else if (component->getName() == "TiledMap")
		{
			TiledMapComponent* tmc = static_cast<TiledMapComponent*>(component);
			assert(tmc->getTMXTiledMap());
			addChild(tmc->getTMXTiledMap());
		}
		else if (component->getName() == "DebugNode")
		{
			DebugNodeComponent* debugNode = static_cast<DebugNodeComponent*>(component);
			// High Z Order = to be drawn on the highest layer
			addChild(debugNode->getDebugNode(), 100);
			addChild(debugNode->getAABBDebugNode(), 100);
		}

		return Node::addComponent(component);
	}
};

#endif // __GAMEENTITY_H__

