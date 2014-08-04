#include "Metronome.h"

Metronome::Metronome() : SonarinGameObject() {
}

void Metronome::load(std::unique_ptr<LoaderParams> const &params) {
	// inherited load function
	SonarinGameObject::load(std::move(params));
}