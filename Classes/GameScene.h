#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Level.h"

class KeyboardInputSystem;
class CollisionResolutionSystem;
class TransformSystem;
class ActionSystem;
class PhysicsSystem;

class GameScene : public cocos2d::LayerColor
{
private:
	cocos2d::Size _visibleSize;
	cocos2d::Point _origin;
	
	KeyboardInputSystem* _inputSystem;
	CollisionResolutionSystem* _collisionResolutionSystem;
	TransformSystem* _transformSystem;
	ActionSystem* _actionSystem;
	PhysicsSystem* _physicsSystem;

	// Level 1
	Level* _level;

	void createDebugInfo();
	void createGameScreen();
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float dt);
};

#endif // __GAMESCENE_H__
