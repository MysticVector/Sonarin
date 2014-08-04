#include "MetronomePendulum.h"

MetronomePendulum::MetronomePendulum() 
	: SonarinGameObject(), 
	directionForward(false),
	angularVelocity(2),
	angularAcceleration(0)
	{
}

void MetronomePendulum::load(std::unique_ptr<LoaderParams> const &params) {
	// inherited load function
	SonarinGameObject::load(std::move(params));
}

void MetronomePendulum::update() {

	angularAcceleration = m_angle / 80;

	angularVelocity += angularAcceleration;

	if (directionForward) {
		m_angle += angularVelocity;
	} else {
		m_angle -= angularVelocity;
	}

	if (m_angle >= 40 || m_angle <= -40)
		directionForward = !directionForward;

	//std::cout << m_angle << " " << angularVelocity << " " << angularAcceleration << std::endl;
}