#include "PlayState.h"

#include <iostream>

#include <GameObjectFactory.h>
#include <InputHandler.h>
#include <LoaderParams.h>
#include <TextureManager.h>

#include "Player.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PlayState::render()
{
	if (m_loadingComplete)
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool PlayState::onEnter()
{
	Player* p = (Player*)TheGameObjectFactory::Instance()->create("Player");

	TheTextureManager::Instance()->load("Assets\\player.png", "player");
	p->load(std::unique_ptr<LoaderParams>(new LoaderParams(100, 100, 64, 64, "player", 1)));

	if (p != NULL)
	{
		m_gameObjects.push_back(p);

		m_loadingComplete = true;
	}

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	m_exiting = true;

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();

		delete m_gameObjects[i];
		m_gameObjects[i] = NULL;
	}

	TheInputHandler::Instance()->reset();

	std::cout << "exiting PlayState\n";
	return true;
}
