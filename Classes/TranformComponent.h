#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "cocos2d.h"

class TransformComponent : public cocos2d::Component
{
public:
	TransformComponent() { _name = "Transform"; }
	virtual ~TransformComponent() {}

	// The current position
	cocos2d::Vec2 pos;

	// The position to be applied next frame
	cocos2d::Vec2 nextPos;
};

#endif // __TRANSFORM_COMPONENT_H__