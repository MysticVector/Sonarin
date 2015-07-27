#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Level.h"

class GameEntity;
class KeyboardInputSystem;
class ActionSystem;

class GameScene : public cocos2d::LayerColor
{
private:
	cocos2d::Size _visibleSize;
	cocos2d::Point _origin;

	// Player
	GameEntity *_sona;

	KeyboardInputSystem* _inputSystem;
	ActionSystem* _actionSystem;

	// Level 1
	Level *_level;

	void createGameScreen();
public:
	~GameScene();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float dt);
};

#endif // __GAMESCENE_H__
