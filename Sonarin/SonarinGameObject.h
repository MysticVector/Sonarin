#ifndef __SONARIN_GAME_OBJECT__
#define __SONARIN_GAME_OBJECT__

#include <AbstractGameObject.h>

class SonarinGameObject : public AbstractGameObject
{
public:
	virtual ~SonarinGameObject() {}

	virtual void load(std::unique_ptr<LoaderParams> const &params);

	virtual void draw();
	virtual void update();

	virtual void clean() {}
	virtual void collision() {}

	virtual std::string type() const { return "SonarinGameObject"; }

protected:
	SonarinGameObject();

	int m_moveSpeed;

	bool m_flipped;

	bool m_moveLeft;
	bool m_moveRight;
	bool m_running;
};

#endif /* defined(__SONARIN_GAME_OBJECT__) */
