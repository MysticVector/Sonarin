#include "DebugNodeComponent.h"

USING_NS_CC;

DebugNodeComponent::~DebugNodeComponent()
{
	CC_SAFE_RELEASE(_debugNode);
}

bool DebugNodeComponent::init()
{
	_name = "DebugNode";
	_debugNode = DrawNode::create();
	_debugNode->setAnchorPoint(cocos2d::Vec2(0, 0));
	CC_SAFE_RETAIN(_debugNode);

	_AABBDebugNode = DrawNode::create();
	_AABBDebugNode->setAnchorPoint(cocos2d::Vec2(0, 0));
	CC_SAFE_RETAIN(_AABBDebugNode);
	
	return true;
}

void DebugNodeComponent::drawRect(Rect r, Rect aabb, float rotation)
{
	_debugNode->clear();
	if (rotation != 0)
	{
		// Changing the content size to take the anchor into consideration
		// Anchor at the top left of the rectangle, in order to do a rotation the same way it was done in Tiled Map Editor
		// And return the rectangle the same position it had in the Tiled Map Editor
		// (the positions get converted to cocos2d's inverted axis upon loading the TMX file)
		_debugNode->setContentSize(r.size);
		_debugNode->setAnchorPoint(cocos2d::Vec2(0, 1));
		_debugNode->setPositionY(r.origin.y + r.size.height);
		_debugNode->setRotation(rotation);

		// Drawing the actual rotated rectangle
		_debugNode->drawRect(r.origin, r.origin + r.size, Color4F::RED);

		// Drawing the AABB
		_AABBDebugNode->drawRect(aabb.origin, aabb.origin + aabb.size, Color4F::WHITE);
	}
	else
	{
		_debugNode->drawRect(r.origin, r.origin + r.size, Color4F::WHITE);
	}
}

void DebugNodeComponent::drawPoint(Vec2 p)
{
	_debugNode->clear();
	_debugNode->drawPoint(p, 5, Color4F::WHITE);
}

void DebugNodeComponent::drawLine(Vec2 p1, Vec2 p2)
{
	_debugNode->clear();

	_debugNode->drawLine(p1, p2, Color4F::WHITE);
}

void DebugNodeComponent::drawLines(std::vector<Vec2> points, Vec2 origin)
{
	_debugNode->clear();

	// Loop through points 2 by 2
	for (unsigned int i = 0; i < points.size() - 1; i += 2)
	{
		_debugNode->drawLine(origin + points[i], origin + points[i + 1], Color4F::WHITE);
	}
}

void DebugNodeComponent::drawPoly(Vec2* points, int nbPoints)
{
	_debugNode->clear();

	_debugNode->drawPoly(points, nbPoints, true, Color4F::WHITE);
}