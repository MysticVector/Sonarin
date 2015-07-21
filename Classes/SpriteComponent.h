#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "cocos2d.h"

class SpriteComponent : public cocos2d::Component
{
public:
	SpriteComponent() { _name = "Sprite"; }
	virtual ~SpriteComponent();

	virtual bool init(cocos2d::Node* owner);
	virtual bool init(cocos2d::Node* owner, std::string file);

	cocos2d::Sprite* _sprite;
};

#endif // __SPRITE_COMPONENT_H__