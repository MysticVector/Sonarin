#include <iostream>
#include <SDLWrapper.h>
#include <Timer.h>

#include "SonarinGame.h"

const int FRAMES_PER_SECOND = 60;
const int TIME_PER_FRAME = 1000 / FRAMES_PER_SECOND;

int main(int argc, char **argv)
{
	Timer fpsSync;

	std::cout << "game init attempt...\n";
	if (TheSonarinGame::Instance()->init("Sonarin", 100, 100, 800, 600, false))
	{
		std::cout << "game init success!\n";
		while (TheSonarinGame::Instance()->running())
		{
			fpsSync.start();

			TheSonarinGame::Instance()->handleEvents();
			TheSonarinGame::Instance()->update();
			TheSonarinGame::Instance()->render();

			// We test here if the loop iteration took less than the time per frame (which is 1/MAX_FPS)
			if (TIME_PER_FRAME > fpsSync.getTime())
			{
				// On attend jusqu'à la fin du temps reservé à l'image actuelle
				TheSDLWrapper::Instance()->delay(TIME_PER_FRAME - fpsSync.getTime());
			}
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "game closing...\n";
	TheSonarinGame::Instance()->clean();

	return 0;
}