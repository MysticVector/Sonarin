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

	m_center.setX((float)params->getCenterX());
	m_center.setY((float)params->getCenterY());

	m_textureID = params->getTextureID();
}

void SonarinGameObject::draw()
{
	TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_center, m_alpha);
}

void SonarinGameObject::update()
{
	// Apply velocity to current position
	m_position += m_velocity;

	// Updating the animation
	GameObject::setCurrentAnim(0);

	if (m_currentAnim != NULL) {
		if (m_animTimer.check()) {
			++m_currentFrame;
			if (m_currentFrame >= m_currentAnim->getNumFrames()) {
				m_currentFrame = 0;
			}
		}
	}
}