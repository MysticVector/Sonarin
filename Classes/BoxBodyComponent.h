#ifndef __BOX_BODY_COMPONENT_H__
#define __BOX_BODY_COMPONENT_H__

#include "cocos2d.h"
#include "BodyComponent.h"

class BoxBodyComponent : public BodyComponent
{
public:
	CREATE_FUNC(BoxBodyComponent);

	virtual ~BoxBodyComponent()	{	CC_SAFE_RELEASE(_boxShape);	}

	virtual bool init()
	{
		_name = "BoxBody";
		_boxShape = nullptr;
		return true;
	}

	void setSize(cocos2d::Size size)
	{
		_size = size;

		CC_SAFE_RELEASE(_boxShape);
		_boxShape = cocos2d::PhysicsShapeBox::create(_size);
		CC_SAFE_RETAIN(_boxShape);
	}

	cocos2d::Size getSize() const { return _size; }

	virtual bool containsPoint(cocos2d::Vec2 p)	{	return _boxShape?(_boxShape->containsPoint(p)):false;	}

protected:
	cocos2d::Size _size;
	cocos2d::PhysicsShapeBox* _boxShape;
};

#endif // __BOX_BODY_COMPONENT_H__