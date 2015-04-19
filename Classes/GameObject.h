#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "cocos2d.h"

class GameObject : public cocos2d::Sprite
{
protected:
	virtual void drawDebug();

public:
	CC_SYNTHESIZE(cocos2d::Vec2, _nextPosition, NextPosition);

	CC_SYNTHESIZE(cocos2d::DrawNode*, _debugNode, DebugNode);
	CC_SYNTHESIZE(bool, _showDebug, ShowDebug);

	GameObject();
	~GameObject();

	virtual void move(cocos2d::Vec2 velocity);
};

#endif // __GAMEOBJECT_H__

