#ifndef __DEBUG_NODE_COMPONENT_H__
#define __DEBUG_NODE_COMPONENT_H__

#include "cocos2d.h"

class DebugNodeComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(DebugNodeComponent);

	virtual ~DebugNodeComponent();

	virtual bool init();

	CC_SYNTHESIZE(cocos2d::DrawNode*, _debugNode, DebugNode);
	CC_SYNTHESIZE(cocos2d::DrawNode*, _AABBDebugNode, AABBDebugNode);

	void drawRect(cocos2d::Rect r, cocos2d::Rect aabb = cocos2d::Rect::ZERO, float rotation = 0);
	void drawPoint(cocos2d::Vec2 p);
	void drawLine(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	void drawLines(std::vector<cocos2d::Vec2> points, cocos2d::Rect aabb = cocos2d::Rect::ZERO, cocos2d::Vec2 origin = cocos2d::Vec2::ZERO);
	void drawPoly(cocos2d::Vec2* points, int nbPoints);
};

#endif // __DEBUG_NODE_COMPONENT_H__