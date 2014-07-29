#include "PlayState.h"

#include <iostream>

#include <GameObjectFactory.h>
#include <InputHandler.h>
#include <LoaderParams.h>
#include <TextureManager.h>

#include "Sona.h"

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
	Sona* p = (Sona*)TheGameObjectFactory::Instance()->create("Sona");

	TheTextureManager::Instance()->load("Assets\\player.png", "sona");
	p->load(std::unique_ptr<LoaderParams>(new LoaderParams(100, 450, 64, 64, "sona")));

	p->addAnim(0, 1, 100, false);		// Standing animation
	p->addAnim(1, 8, 80, true);			// Running animation
	p->addAnim(2, 8, 100, true);		// Walking animation
	p->addAnim(3, 5, 100, false);		// Jumping animation
	p->addAnim(4, 1, 100, false);		// Falling animation

	p->setCurrentAnim(0);

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
