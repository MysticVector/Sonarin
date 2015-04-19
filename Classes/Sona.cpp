#include "Sona.h"

USING_NS_CC;

Sona::~Sona()
{
}

Sona::Sona() 
{
}

Sona* Sona::create()
{
	Sona *player = new Sona();
	if (player && player->init("sona.png"))
	{
		player->autorelease();
		return player;
	}
	else
	{
		delete player;
		player = NULL;
		return NULL;
	}
}

bool Sona::init(std::string file)
{
	if (!GameObject::initWithFile(file))
	{
		return false;
	}

	addChild(_debugNode, 10);

	PhysicsBody *body = PhysicsBody::createBox(Size(getBoundingBox().size),
		PhysicsMaterial(1.f, 0.0f, 0.0f), Vec2(-9, 0));
	body->setDynamic(true);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setRotationEnable(false);
	setPhysicsBody(body);

	return true;
}

void Sona::update(float dt)
{
}

Rect Sona::getBoundingBox() const
{
	return Rect(Node::getBoundingBox().origin.x + 15, Node::getBoundingBox().origin.y + 4,
		Node::getBoundingBox().size.width - 48, Node::getBoundingBox().size.height - 4);
}

void Sona::move(Vec2 velocity)
{
	getPhysicsBody()->applyForce(velocity);
}