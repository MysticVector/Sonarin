#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Sona.h"
#include "Level.h"
#include "MoveCommand.h"

class GameScene : public cocos2d::LayerColor
{
private:
	cocos2d::Size _visibleSize;
	cocos2d::Point _origin;

	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

	Command *_moveRightCommand;
	Command *_moveLeftCommand;

	// Player
	Sona *_sona;

	// Level 1
	Level *_level;

	void createGameScreen();

	Command* handleInput();

public:
	~GameScene();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float dt);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode keyCode);
};

#endif // __GAMESCENE_H__
