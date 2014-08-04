#ifndef __METRONOME_PENDULUM__
#define __METRONOME_PENDULUM__

#include <iostream>
#include <vector>

#include <GameObjectFactory.h>

#include "SonarinGameObject.h"

/*
===============================================================================
Represents the metronome pendulum that keeps swinging
===============================================================================
*/
class MetronomePendulum : public SonarinGameObject {
public:
	MetronomePendulum();
	virtual ~MetronomePendulum() { }

	virtual void load(std::unique_ptr<LoaderParams> const &params);

	virtual void update();

	virtual std::string type() const { return "MetronomePendulum"; }
private:
	bool directionForward;
	double angularVelocity;
	double angularAcceleration;
};

/*
===============================================================================
Creator class for MetronomePendulum
===============================================================================
*/
class MetronomePendulumCreator : public BaseCreator {
	SonarinGameObject* createGameObject() const {
		return new MetronomePendulum();
	}
};


#endif /* defined(__METRONOME_PENDULUM__) */
