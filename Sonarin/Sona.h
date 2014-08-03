#ifndef __SONA__
#define __SONA__

#include <iostream>
#include <vector>

#include <GameObjectFactory.h>

#include "SonarinGameObject.h"

/*
===============================================================================
	Represents the main character Sona which is controllable by the player
===============================================================================
*/
class Sona : public SonarinGameObject
{
public:
	Sona();
	virtual ~Sona() {}

	virtual void load(std::unique_ptr<LoaderParams> const &params);

	virtual void draw();
	virtual void update();

	virtual std::string type() const { return "Sona"; }

private:
	/*
	====================
	handleInput
		Handle any input from the keyboard or joystick
	====================
	*/
	void handleInput();

	/*
	====================
	handleAnimation
		Handle any animation for Sona
	====================
	*/
	void handleAnimation();


	void doJumpAnimation();

	/*
	====================
	handleMovement
		Handle Sona's movement
	====================
	*/
	void handleMovement(Vector2D velocity);

	bool m_pressedJump;
	int m_minJumpHeight;
	int m_maxJumpHeight;
};

/*
===============================================================================
	Creator class for Sona
===============================================================================
*/
class SonaCreator : public BaseCreator
{
	SonarinGameObject* createGameObject() const
	{
		return new Sona();
	}
};


#endif /* defined(__PLAYER__) */
