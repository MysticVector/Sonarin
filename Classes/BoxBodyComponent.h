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
		_rotation = 0;
		_rect = cocos2d::Rect::ZERO;
		_AABB = cocos2d::Rect::ZERO;
		return true;
	}

	void setRect(const cocos2d::Rect& rect) {	_rect = rect;	}
	cocos2d::Rect& getRect() { return _rect; }

	void setAABB(const cocos2d::Rect& aabb) { _AABB = aabb; }
	cocos2d::Rect& getAABB() { return _AABB; }

	static bool containsPoint(cocos2d::Rect r, cocos2d::Vec2 p, float rectAngle = 0)
	{
		if (rectAngle != 0)
		{
			// Anchor point needs to be on the top left of the rectangle, to match the angle read from the TMX Map
			// Coz that's how the rotation was done on the Tiled Map Editor
			auto pointAnchor = cocos2d::Node::create();
			cocos2d::Vec2 anchor = cocos2d::Vec2(r.origin.x, r.origin.y + r.size.height);
			pointAnchor->setPosition(anchor);

			// Position relative to the anchor
			auto point = cocos2d::Node::create();
			point->setPosition(p - anchor);

			// Rotate point to be able to test it against an unrotated rectangle
			pointAnchor->setRotation(-rectAngle);

			p = pointAnchor->convertToWorldSpace(point->getPosition());
		}
		
		return r.containsPoint(p);

	}

	CC_SYNTHESIZE(float, _rotation, Rotation);
protected:
	cocos2d::Rect _rect;
	cocos2d::Rect _AABB;
};

#endif // __BOX_BODY_COMPONENT_H__