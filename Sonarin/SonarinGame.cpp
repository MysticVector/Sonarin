#include "SonarinGame.h"

#include <Game.h>
#include <GameObjectFactory.h>
#include <GameStateMachine.h>

#include "Sona.h"
#include "PlayState.h"

SonarinGame* SonarinGame::s_instance = NULL;

SonarinGame* SonarinGame::Instance()
{
	if (s_instance == NULL)
	{
		s_instance = new SonarinGame();
		return s_instance;
	}

	return s_instance;
}

void SonarinGame::clean()
{
	if (s_instance != NULL)
	{
		delete s_instance;
		s_instance = NULL;
	}
}

bool SonarinGame::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// Calling the generic Game init function from the parent class
	Game::init(title, xpos, ypos, width, height, fullscreen);

	// register the types for the game
	TheGameObjectFactory::Instance()->registerType("Sona", new SonaCreator());

	// start the first state
	TheGameStateMachine::Instance()->changeState(new PlayState());

	return true;
}

SonarinGame::~SonarinGame()
{
	std::cout << "cleaning game\n";

	TheGameObjectFactory::Clean();
	TheGameStateMachine::Clean();
}