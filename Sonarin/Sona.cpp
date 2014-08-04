#include "Sona.h"

#include <Animation.h>
#include <IntervalTimer.h>

#include "SonarinGame.h"
#include "InputHandler.h"
#include "TextureManager.h"

Sona::Sona() : SonarinGameObject(), m_pressedJump(false) {
	m_running = false;
	m_minJumpHeight = 90;
	m_maxJumpHeight = 130;
}

void Sona::load(std::unique_ptr<LoaderParams> const &params) {
	// inherited load function
	SonarinGameObject::load(std::move(params));

	m_moveSpeed = 3;
}

void Sona::draw() {
	if (m_flipped) {
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_center, m_alpha, SDL_FLIP_HORIZONTAL);
	} else {
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_center, m_alpha);
	}
}

void Sona::update() {
	handleInput();

	if (m_moveLeft) {
		if (m_running) {
			m_velocity.setX(-5);
		} else {
			m_velocity.setX(-2);
		}
	} else if (m_moveRight) {
		if (m_running) {
			m_velocity.setX(5);
		} else {
			m_velocity.setX(2);
		}
	} else {
		m_velocity.setX(0);
	}

	// Give the ability to make a small jump or a bigger one depending on how much the jump button is pressed
	if (m_position.getY() < SonarinGame::Instance()->getWindowHeight() - m_maxJumpHeight || 
		(m_pressedJump == false && m_position.getY() < SonarinGame::Instance()->getWindowHeight() - m_minJumpHeight)) {
		m_jumping = false;
	}

	if (!m_jumping) {
		m_velocity.setY(4);
	} else {
		m_velocity.setY(-4);
	}

	handleMovement(m_velocity);

	handleAnimation();
}

void Sona::handleAnimation() {
	if (m_velocity.getY() < 0) {			// Jumping
		if (m_currentAnim->getAnimID() != 3) {
			m_currentAnim = m_animList[3];
			m_currentFrame = 0;
		}
		
	} else if (m_velocity.getY() > 0) {		// Falling
		if (m_currentAnim->getAnimID() != 4) {
			m_currentAnim = m_animList[4];
			m_currentFrame = 0;
		}
	} else {
		if (m_velocity.getX() == 0) {		// Standing
			if (m_currentAnim->getAnimID() != 0) {
				m_currentAnim = m_animList[0];
				m_currentFrame = 0;
			}
		} else {

			if (m_running) {				// Running
				if (m_currentAnim->getAnimID() != 1) {
					m_currentAnim = m_animList[1];
					m_currentFrame = 0;
				}
			} else {						// Walking
				if (m_currentAnim->getAnimID() != 2) {
					m_currentAnim = m_animList[2];
					m_currentFrame = 0;
				}
			}
		}
	}

	if (m_velocity.getX() < 0)		// Direction of movement
		m_flipped = true;
	else
		m_flipped = false;

	m_animTimer.setInterval(m_currentAnim->getAnimSpeed());
	m_currentRow = m_currentAnim->getAnimRow();
	
	if (m_animTimer.check()) {
		if (m_currentAnim->isLooped()) {
			++m_currentFrame;
			if (m_currentFrame >= m_currentAnim->getNumFrames()) {
				m_currentFrame = 0;
			}
		} else {
			if (m_currentFrame < m_currentAnim->getNumFrames() - 1) {
				++m_currentFrame;
			}
		}
	}
}

void Sona::handleMovement(Vector2D velocity) {
	// get the current position
	Vector2D newPos = m_position;

	// add velocity to the x position
	newPos.setX(m_position.getX() + velocity.getX());

	m_position.setX(newPos.getX());

	// add velocity to y position
	newPos.setY(newPos.getY() + velocity.getY());

	// check if new y position would collide with a tile
	if ((newPos.getY() + m_height) < SonarinGame::Instance()->getWindowHeight()) {
		// no collision, add to the actual x position
		m_position.setY(newPos.getY());
	} else {
		// collision, stop y movement
		m_velocity.setY(0);

		// allow the player to jump again
		m_canJump = true;

		m_jumping = false;
	}
}

void Sona::handleInput() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_RIGHT))) {
		if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_a))) {
			m_running = true;
		} else {
			m_running = false;
		}

		m_moveRight = true;
		m_moveLeft = false;
	} else if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_LEFT))) {
		if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_a))) {
			m_running = true;
		} else {
			m_running = false;
		}

		m_moveRight = false;
		m_moveLeft = true;
	} else {
		m_moveRight = false;
		m_moveLeft = false;
	}


	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_canJump && !m_pressedJump) {
		if (!m_pressedJump) {
			m_jumping = true;
			m_canJump = false;
			m_pressedJump = true;
			m_running = false;
		}
	}

	if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
		m_pressedJump = false;
	}
}