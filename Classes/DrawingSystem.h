#ifndef __DRAWING_SYSTEM_H__
#define __DRAWING_SYSTEM_H__

#include "cocos2d.h"

class DrawingSystem : public cocos2d::Ref
{
public:
	static DrawingSystem* create(cocos2d::Node* owner);

	virtual bool init(cocos2d::Node* owner)
	{
		_owner = owner;
		return true;
	}

	void draw();

private:
	// The parent scene where all entities can be accessed
	cocos2d::Node* _owner;
};

#endif // __DRAWING_SYSTEM_H__