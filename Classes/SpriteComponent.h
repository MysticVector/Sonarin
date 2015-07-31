#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "cocos2d.h"

class SpriteComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(SpriteComponent);

	virtual ~SpriteComponent();

	virtual bool init();

	virtual void setSpriteFile(std::string file);

	CC_SYNTHESIZE(cocos2d::Sprite*, _sprite, Sprite);
};

#endif // __SPRITE_COMPONENT_H__