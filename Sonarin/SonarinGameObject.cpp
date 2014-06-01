#include "SonarinGameObject.h"

#include <LoaderParams.h>
#include <TextureManager.h>


SonarinGameObject::SonarinGameObject() : AbstractGameObject(),
m_moveSpeed(0)
{
}

void SonarinGameObject::load(std::unique_ptr<LoaderParams> const &params)
{
	// get position
	m_position = Vector2D((float)params->getX(), (float)params->getY());

	// get drawing variables
	m_width = params->getWidth();
	m_height = params->getHeight();
	m_textureID = params->getTextureID();
	m_numFrames = params->getNumFrames();
}

// draw the object to the screen
void SonarinGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_alpha);
}

// apply velocity to current position
void SonarinGameObject::update()
{
	m_position += m_velocity;
	m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % m_numFrames);
}