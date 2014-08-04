#include "PlayState.h"

#include <iostream>

#include <GameObjectFactory.h>
#include <InputHandler.h>
#include <LoaderParams.h>
#include <TextureManager.h>

#include "Metronome.h"
#include "MetronomePendulum.h"
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
	// Loading the player
	Sona* p = (Sona*)TheGameObjectFactory::Instance()->create("Sona");

	TheTextureManager::Instance()->load("Assets\\sona.png", "sona");
	p->load(std::unique_ptr<LoaderParams>(new LoaderParams(100, 450, 64, 64, 32, 32, "sona")));

	p->addAnim(0, 1, 100, false);		// Standing animation
	p->addAnim(1, 8, 80, true);			// Running animation
	p->addAnim(2, 8, 100, true);		// Walking animation
	p->addAnim(3, 5, 100, false);		// Jumping animation
	p->addAnim(4, 1, 100, false);		// Falling animation

	p->setCurrentAnim(0);

	if (p != NULL) {
		m_gameObjects.push_back(p);
	}
	
	// Loading the metronome body
	Metronome* m = (Metronome*)TheGameObjectFactory::Instance()->create("Metronome");

	TheTextureManager::Instance()->load("Assets\\metronome_body.png", "metronome");
	m->load(std::unique_ptr<LoaderParams>(new LoaderParams(650, 0, 121, 200, 75, 100, "metronome")));

	if (m != NULL) {
		m_gameObjects.push_back(m);
	}

	// Loading the metronome pendulum
	MetronomePendulum* mp = (MetronomePendulum*)TheGameObjectFactory::Instance()->create("MetronomePendulum");

	TheTextureManager::Instance()->load("Assets\\metronome_pendulum.png", "metronome_pendulum");
	mp->load(std::unique_ptr<LoaderParams>(new LoaderParams(701, 26, 18, 148, 9, 139, "metronome_pendulum")));

	if (mp != NULL) {
		m_gameObjects.push_back(mp);
	}

	m_loadingComplete = true;

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
