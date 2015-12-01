#ifndef __BOX_BODY_COMPONENT_H__
#define __BOX_BODY_COMPONENT_H__

#include "cocos2d.h"

class BoxBodyComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(BoxBodyComponent);
	virtual bool init()
	{
		_name = "BoxBody";
		return true;
	}

	void setRect(cocos2d::Rect rect) {	_rect = rect;	}
	cocos2d::Rect& getRect() { return _rect; }

	static bool containsPoint(cocos2d::Rect r, cocos2d::Vec2 p) {	return r.containsPoint(p);	}

protected:
	cocos2d::Rect _rect;
};

#endif // __BOX_BODY_COMPONENT_H__