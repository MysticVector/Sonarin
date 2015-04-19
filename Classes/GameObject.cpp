#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject()
{
	_debugNode = DrawNode::create();
	_showDebug = false;
}

GameObject::~GameObject()
{
}

void GameObject::drawDebug()
{
}

void GameObject::move(Vec2 velocity)
{
}