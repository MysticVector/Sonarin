#include <iostream>
#include <Game.h>

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char **argv)
{
	Uint32 frameStart, frameTime;

	std::cout << "game init attempt...\n";
	if (TheGame::Instance()->init("Sonarin", 100, 100, 800, 600, false))
	{
		std::cout << "game init success!\n";
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "game closing...\n";
	TheGame::Instance()->clean();

	return 0;
}