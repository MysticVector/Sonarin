#include "SonarinGameObject.h"

#include <Animation.h>
#include <IntervalTimer.h>
#include <LoaderParams.h>
#include <TextureManager.h>


SonarinGameObject::SonarinGameObject() : GameObject(), m_moveSpeed(0) { }

void SonarinGameObject::load(std::unique_ptr<LoaderParams> const &params)
{
	// get position
	m_position = Vector2D((float)params->getX(), (float)params->getY());

	// get drawing variables
	m_width = params->getWidth();
	m_height = params->getHeight();
	m_textureID = params->getTextureID();
}

void SonarinGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_alpha);
}

void SonarinGameObject::update()
{
	// Apply velocity to current position
	m_position += m_velocity;


	// Updating the animation
	m_currentAnim = m_animList[0];

	m_animTimer.setInterval(m_currentAnim->getAnimSpeed());
	m_currentRow = m_currentAnim->getAnimRow();

	if (m_animTimer.check()) {
		if (m_currentFrame < m_currentAnim->getNumFrames()) {
			++m_currentFrame;
		} else if (m_currentAnim->isLooped()) {
			m_currentFrame = 0;
		}
	}
}