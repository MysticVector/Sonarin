#ifndef __BODY_COMPONENT_H__
#define __BODY_COMPONENT_H__

#include "cocos2d.h"

class BodyComponent : public cocos2d::Component
{
public:
	virtual bool containsPoint(cocos2d::Vec2 p) = 0;
};

#endif // __BODY_COMPONENT_H__