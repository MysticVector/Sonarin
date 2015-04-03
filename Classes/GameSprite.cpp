#include "GameSprite.h"

USING_NS_CC;

GameSprite::GameSprite()
	: _velocity(Point(0, 0))
	, _screenSize(CCDirector::getInstance()->getWinSize())
{
	_debugNode = DrawNode::create();

	_showDebug = false;
}

GameSprite::~GameSprite()
{
}