#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "cocos2d.h"

class TransformComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(TransformComponent);

	virtual bool init()
	{
		_name = "Transform";
		_nextPosition = cocos2d::Vec2::ZERO;
		return true;
	}

	void setNextPosition(cocos2d::Vec2 nextPosition) { _nextPosition = nextPosition; }
	cocos2d::Vec2& getNextPosition() { return _nextPosition; }

	// Changing the parent entity's position to apply the changes from last frame
	void commitPosition()	{	_owner->setPosition(_nextPosition); 	}
protected:
	// The position to apply next frame
	cocos2d::Vec2 _nextPosition;
};

#endif // __TRANSFORM_COMPONENT_H__