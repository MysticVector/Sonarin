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

void DebugNodeComponent::drawPoint(Vec2 p)
{
	_debugNode->clear();
	_debugNode->drawPoint(p, 5, Color4F::WHITE);
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