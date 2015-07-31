#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "cocos2d.h"

class TransformComponent : public cocos2d::Component
{
	friend class ActionSystem;
public:
	CREATE_FUNC(TransformComponent);

	virtual bool init()
	{
		_name = "Transform";
		_pos = cocos2d::Vec2::ZERO;
		_nextPos = cocos2d::Vec2::ZERO;
		return true;
	}

	// The current position
	CC_SYNTHESIZE(cocos2d::Vec2, _pos, Pos);

	// The position to be applied next frame
	CC_SYNTHESIZE(cocos2d::Vec2, _nextPos, NextPos);
};

#endif // __TRANSFORM_COMPONENT_H__