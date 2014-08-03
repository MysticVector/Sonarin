#ifndef __METRONOME__
#define __METRONOME__

#include <iostream>
#include <vector>

#include <GameObjectFactory.h>

#include "SonarinGameObject.h"

/*
===============================================================================
Represents the metronome that shows the timing with which the play can sync his actions
===============================================================================
*/
class Metronome : public SonarinGameObject {
public:
	Metronome();
	virtual ~Metronome() { }

	virtual void load(std::unique_ptr<LoaderParams> const &params);

	virtual void draw();

	virtual std::string type() const { return "Metronome"; }

};

/*
===============================================================================
Creator class for Metronome
===============================================================================
*/
class MetronomeCreator : public BaseCreator {
	SonarinGameObject* createGameObject() const {
		return new Metronome();
	}
};


#endif /* defined(__METRONOME__) */
