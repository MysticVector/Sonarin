#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "cocos2d.h"

class GameEntity;

class MovementSystem : public cocos2d::Ref
{
public:
	virtual ~MovementSystem() {}

	// Methods to handle the observing components (Observer Pattern)
	void registerEntity(GameEntity* e);
	void unregisterEntity(GameEntity* e);

	void update(float dt);

private:
	// List of observing entities
	cocos2d::Vector<GameEntity*> _entities;
};

#endif // __MOVEMENT_SYSTEM_H__