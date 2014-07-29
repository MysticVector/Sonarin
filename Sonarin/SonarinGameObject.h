#ifndef __SONARIN_GAME_OBJECT__
#define __SONARIN_GAME_OBJECT__

#include <GameObject.h>

/*
===============================================================================
	Represents Sonarin's generic game objects
===============================================================================
*/
class SonarinGameObject : public GameObject
{
public:
	virtual void load(std::unique_ptr<LoaderParams> const &params);

	virtual void draw();
	virtual void update();

	virtual void collision() {}

	virtual std::string type() const { return "SonarinGameObject"; }

protected:
	SonarinGameObject();

	int m_moveSpeed;

	bool m_flipped;

	bool m_moveLeft;
	bool m_moveRight;

	bool m_running;

	bool m_canJump;
	bool m_jumping;
	int m_jumpHeight;
};

#endif /* defined(__SONARIN_GAME_OBJECT__) */
