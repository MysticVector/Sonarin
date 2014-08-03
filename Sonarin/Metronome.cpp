#include "Metronome.h"

#include <Animation.h>
#include <IntervalTimer.h>

#include "SonarinGame.h"
#include "TextureManager.h"

Metronome::Metronome() : SonarinGameObject() {
}

void Metronome::load(std::unique_ptr<LoaderParams> const &params) {
	// inherited load function
	SonarinGameObject::load(std::move(params));
}

void Metronome::draw() {
	TheTextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_alpha);
}