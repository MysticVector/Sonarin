#include "Player.h"

#include "InputHandler.h"
#include "TextureManager.h"

Player::Player() : SonarinGameObject()
{
}

void Player::load(std::unique_ptr<LoaderParams> const &params)
{
	// inherited load function
	SonarinGameObject::load(std::move(params));

	m_moveSpeed = 3;
}

void Player::draw()
{
	if (m_flipped)
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_alpha);
	}
}

void Player::update()
{
	handleInput();

	if (m_moveLeft)
	{
		if (m_running)
		{
			m_velocity.setX(-5);
		}
		else
		{
			m_velocity.setX(-2);
		}
	}
	else if (m_moveRight)
	{
		if (m_running)
		{
			m_velocity.setX(5);
		}
		else
		{
			m_velocity.setX(2);
		}
	}
	else
	{
		m_velocity.setX(0);
	}

	handleMovement(m_velocity);

	handleAnimation();
}

void Player::clean()
{
	SonarinGameObject::clean();
}

void Player::handleAnimation()
{
	if (m_velocity.getY() < 0)			// Jumping
	{
		m_currentFrame = 2;
		m_currentRow = 2;
		m_numFrames = 2;
	}
	else if (m_velocity.getY() > 0)		// Falling
	{
		m_currentRow = 3;
		m_numFrames = 1;
	}
	else
	{
		if (m_velocity.getX() == 0)		// Standing
		{
			m_currentRow = 0;
			m_numFrames = 1;
		}
		else							// There is some movement
		{
			if (m_velocity.getX() < 0)	// Direction of movement
				m_flipped = true;
			else
				m_flipped = false;

			if (m_running)				// Running
			{
				m_currentRow = 1;
				m_numFrames = 8;
			}
			else						// Walking
			{
				m_currentRow = 2;
				m_numFrames = 8;
			}
		}
	}

	if (m_running)
		m_currentFrame = int((SDL_GetTicks() / (80)) % m_numFrames);
	else
		m_currentFrame = int((SDL_GetTicks() / (100)) % m_numFrames);
}

void Player::handleMovement(Vector2D velocity)
{
	// get the current position
	Vector2D newPos = m_position;

	// add velocity to the x position
	newPos.setX(m_position.getX() + velocity.getX());

	m_position.setX(newPos.getX());

	// add velocity to y position
	newPos.setY(newPos.getY() + velocity.getY());

	m_position.setY(newPos.getY());
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_RIGHT)))
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_a)))
		{
			m_running = true;
		}
		else
		{
			m_running = false;
		}

		m_moveRight = true;
		m_moveLeft = false;
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_LEFT)))
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_GetScancodeFromKey(SDLK_a)))
		{
			m_running = true;
		}
		else
		{
			m_running = false;
		}

		m_moveRight = false;
		m_moveLeft = true;
	}
	else
	{
		m_moveRight = false;
		m_moveLeft = false;
	}
}