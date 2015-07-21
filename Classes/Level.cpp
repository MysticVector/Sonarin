#include "Level.h"

USING_NS_CC;

Level::~Level()
{
}

Level::Level()
{
}

Level* Level::create(std::string levelName, std::string collisionObjectGroupName){
	Level *pRet = new Level();
	if (pRet && pRet->init(levelName, collisionObjectGroupName))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Level::init(std::string levelName, std::string collisionObjectGroupName)
{
	if (!TMXTiledMap::initWithTMXFile(levelName))
	{
		return false;
	}

	_collisionObjectGroup = getObjectGroup(collisionObjectGroupName);

	createPhysicsBody();
	
	return true;
}

void Level::createPhysicsBody()
{
	for (auto& object : _collisionObjectGroup->getObjects())
	{
		float objectX = object.asValueMap().at("x").asFloat(),
			objectY = object.asValueMap().at("y").asFloat();
		Size s = Size(object.asValueMap().at("width").asFloat(), 
					  object.asValueMap().at("height").asFloat());

		if (object.asValueMap().find("polylinePoints") == object.asValueMap().end())
		{
			PhysicsShapeBox *box = PhysicsShapeBox::create(s, PhysicsMaterial(0.0f, 0.0f, 1.0f),
				Vec2(objectX + s.width / 2, objectY + s.height / 2));
			box->setTag(0);

			PhysicsBody *body = PhysicsBody::create();
			body->setDynamic(false);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->addShape(box);

			Node* node = Node::create();
			node->setPhysicsBody(body);
			addChild(node);
			_physicsNodes.pushBack(node);
		}
		else
		{
			Vec2 t[2];
			int i = 0;
			for (auto& point : object.asValueMap().at("polylinePoints").asValueVector())
			{
				// convert the points' local coordinates to the world coordinates
				// by doing a translation using the object's position vector

				// We invert the local y because it's based on the top-left space in Tiled
				t[i].x = point.asValueMap().at("x").asInt() + objectX;
				t[i].y = -point.asValueMap().at("y").asInt() + objectY;
				i++;
			}
			PhysicsShapeEdgeSegment *line = PhysicsShapeEdgeSegment::create(t[0], t[1], 
				PhysicsMaterial(0.0f, 0.0f, 1.0f));
			line->setTag(0);

			PhysicsBody *body = PhysicsBody::create();
			body->setDynamic(false);
			body->setContactTestBitmask(0xFFFFFFFF);
			body->addShape(line);

			Node* node = Node::create();
			node->setPhysicsBody(body);
			addChild(node);
			_physicsNodes.pushBack(node);
		}
	}
}

void Level::update(float dt)
{

}