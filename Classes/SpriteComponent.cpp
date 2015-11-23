#include "SpriteComponent.h"

USING_NS_CC;

SpriteComponent::~SpriteComponent()
{
	CC_SAFE_RELEASE(_sprite);
}

bool SpriteComponent::init()
{
	_name = "Sprite";
	_sprite = nullptr;
	return true;
}

void SpriteComponent::setSpriteFile(std::string file)
{
	_sprite = Sprite::create(file);
	_sprite->setAnchorPoint(Vec2(0, 0));
	assert(_sprite);
	_sprite->retain();
}