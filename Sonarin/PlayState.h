#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include <vector>

#include <GameState.h>

class SonarinGameObject;

class PlayState : public GameState
{
public:
	virtual ~PlayState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;

	std::vector<SonarinGameObject*> m_gameObjects;
};


#endif /* defined(__PLAY_STATE__) */