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
	return true;
}

void DebugNodeComponent::drawRect(Rect r)
{
	_debugNode->clear();
	_debugNode->drawRect(r.origin, r.origin + r.size, Color4F::WHITE);
}

void DebugNodeComponent::drawRect(Rect r, float rotation)
{
	_debugNode->clear();
	if (rotation != 0)
	{
		// Changing the content size to take the anchor into consideration
		_debugNode->setContentSize(r.size);

		// Anchor at the top left of the rectangle, in order to do a rotation the same way it was done in Tiled Map Editor
		_debugNode->setAnchorPoint(cocos2d::Vec2(0, 1));

		// Return the rectangle the same position it had in the Tiled Map Editor
		// (the positions get converted to cocos2d's inverted axis upon loading the TMX file)
		_debugNode->setPositionY(r.origin.y + r.size.height);

		_debugNode->drawRect(r.origin, r.origin + r.size, Color4F::WHITE);
		_debugNode->setRotation(rotation);

		auto n = DrawNode::create();
		n->drawRect(_debugNode->getBoundingBox().origin,
			_debugNode->getBoundingBox().origin + _debugNode->getBoundingBox().size, Color4F::RED);

		_debugNode->getParent()->addChild(n);
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