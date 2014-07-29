#ifndef __SONARIN_GAME__
#define __SONARIN_GAME__

#include <Game.h>

/*
===============================================================================
	A singleton that handles the state of the whole game
===============================================================================
*/
class SonarinGame : public Game
{
public:
	static SonarinGame* Instance();
	static void clean();

	/*
	====================
	init
		Initializes SDL and creates the in-game state
	====================
	*/
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

private:
	~SonarinGame();

	static SonarinGame* s_instance;

	int m_windowWidth;
	int m_windowHeight;

	bool m_running;
};

typedef SonarinGame TheSonarinGame;

#endif /* defined(__SONARIN_GAME__) */