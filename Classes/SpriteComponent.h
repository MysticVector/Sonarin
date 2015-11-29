#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "cocos2d.h"

class SpriteComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(SpriteComponent);

	virtual ~SpriteComponent() { CC_SAFE_RELEASE(_sprite); }

	virtual bool init()
	{
		_name = "Sprite";
		_sprite = nullptr;
		return true;
	}

	virtual void setSpriteFile(std::string file)
	{
		CC_SAFE_RELEASE(_sprite);
		_sprite = cocos2d::Sprite::create(file);
		_sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		CC_SAFE_RETAIN(_sprite);
		assert(_sprite);
	}

	CC_SYNTHESIZE(cocos2d::Sprite*, _sprite, Sprite);
};

#endif // __SPRITE_COMPONENT_H__