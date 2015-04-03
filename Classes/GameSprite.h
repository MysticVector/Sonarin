#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"

enum
{
	kBackground,
	kMiddleground,
	kForeground
};

enum
{
	kSpriteSona
};

class GameSprite : public cocos2d::Sprite
{
protected:
	cocos2d::Size _screenSize;

	virtual void drawDebug() = 0;

public:
	CC_SYNTHESIZE(cocos2d::Point, _nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::Point, _velocity, Velocity);

	CC_SYNTHESIZE(cocos2d::DrawNode*, _debugNode, DebugNode);
	CC_SYNTHESIZE(bool, _showDebug, ShowDebug);

	GameSprite();
	~GameSprite();
};

#endif // __GAMESPRITE_H__

