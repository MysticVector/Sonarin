#ifndef __SONA_H__
#define __SONA_H__

#include "cocos2d.h"
#include "GameObject.h"


class Sona : public GameObject
{
private:
public:
	Sona();
	~Sona();

	static Sona* create();
	bool init(std::string file);
	virtual void update(float dt);

	virtual cocos2d::Rect getBoundingBox() const;

	virtual void move(cocos2d::Vec2 velocity);
};

#endif // __SONA_H__