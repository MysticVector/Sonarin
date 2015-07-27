#ifndef __ACTION_SYSTEM_H__
#define __ACTION_SYSTEM_H__

#include "cocos2d.h"

class GameEntity;

class ActionSystem : public cocos2d::Ref
{
public:
	virtual ~ActionSystem() {}

	// Methods to handle the observing components (Observer Pattern)
	void registerEntity(GameEntity* e);
	void unregisterEntity(GameEntity* e);

	void update(float dt);

private:
	// List of observing entities
	cocos2d::Vector<GameEntity*> _entities;
};

#endif // __ACTION_SYSTEM_H__