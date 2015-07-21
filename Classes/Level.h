#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"


class Level : public cocos2d::TMXTiledMap
{
private:
	cocos2d::Vector<cocos2d::Node*> _physicsNodes;

	void createPhysicsBody();
public:
	CC_SYNTHESIZE(cocos2d::TMXObjectGroup*, _collisionObjectGroup, CollisionObjectGroup);
	
	Level();
	~Level();

	static Level* create(std::string levelName, std::string collisionLayerName);
	bool init(std::string levelName, std::string collisionLayerName);
	virtual void update(float dt);
};

#endif // __LEVEL_H__