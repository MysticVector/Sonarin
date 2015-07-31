#ifndef __GAMEENTITY_H__
#define __GAMEENTITY_H__

#include "cocos2d.h"
#include "SpriteComponent.h"

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
			if (sc->getSprite() != nullptr)
				addChild(sc->getSprite());
			else
				assert(sc->getSprite());
		}

		return Node::addComponent(component);
	}
};

#endif // __GAMEENTITY_H__

