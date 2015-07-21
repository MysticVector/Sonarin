#include "MovementComponent.h"

USING_NS_CC;

bool MovementComponent::init(const cocos2d::Vec2& speed,
	const cocos2d::Vec2& maxSpeed,
	const cocos2d::Vec2& acc,
	float decX,
	float jumpStartSpeedY)
{
	this-> speed = speed;
	this->maxSpeed = maxSpeed;
	this->acc = acc;
	this->decX = decX;
	this->jumpStartSpeedY = jumpStartSpeedY;

	jumping = false;
	jumpKeyDown = false;

	return true;
}