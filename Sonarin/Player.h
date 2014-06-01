#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <vector>

#include <GameObjectFactory.h>

#include "SonarinGameObject.h"

class Player : public SonarinGameObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void load(std::unique_ptr<LoaderParams> const &params);

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual std::string type() const { return "Player"; }

private:
	// handle any input from the keyboard, mouse, or joystick
	void handleInput();

	// handle any animation for the player
	void handleAnimation();

	void handleMovement(Vector2D velocity);
};

// for the factory
class PlayerCreator : public BaseCreator
{
	SonarinGameObject* createGameObject() const
	{
		return new Player();
	}
};


#endif /* defined(__PLAYER__) */
