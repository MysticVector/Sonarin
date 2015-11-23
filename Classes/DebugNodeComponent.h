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

	void drawRect(cocos2d::Rect r);
	void drawPoint(cocos2d::Vec2 p);
	void drawLines(std::vector<cocos2d::Vec2> points, cocos2d::Vec2 origin = cocos2d::Vec2::ZERO);
};

#endif // __DEBUG_NODE_COMPONENT_H__