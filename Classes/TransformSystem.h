#ifndef __TRANSFORM_SYSTEM_H__
#define __TRANSFORM_SYSTEM_H__

#include "cocos2d.h"

class TransformSystem : public cocos2d::Ref
{
public:
	static TransformSystem* create(cocos2d::Node* owner);

	virtual bool init(cocos2d::Node* owner)
	{
		_owner = owner;
		return true;
	}

	void update(float dt);

private:
	// The parent scene where all entities can be accessed
	cocos2d::Node* _owner;
};

#endif // __TRANSFORM_SYSTEM_H__