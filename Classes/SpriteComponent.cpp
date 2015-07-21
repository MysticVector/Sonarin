#include "SpriteComponent.h"

USING_NS_CC;

SpriteComponent::~SpriteComponent()
{
	CC_SAFE_RELEASE(_sprite);
}

bool SpriteComponent::init(Node* owner)
{
	_sprite = Sprite::create();
	_sprite->retain();

	owner->addChild(_sprite);

	return true;
}

bool SpriteComponent::init(Node* owner, std::string file)
{
	_sprite = Sprite::create(file);
	_sprite->retain();

	owner->addChild(_sprite);

	return true;
}