#include "GameScene.h"
#include "GameEntity.h"
#include "SpriteComponent.h"
#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "KeyboardInputComponent.h"
#include "KeyboardInputSystem.h"
#include "CollisionResolutionSystem.h"
#include "TransformSystem.h"
#include "ActionSystem.h"
#include "PhysicsSystem.h"
#include "ActionComponent.h"
#include "MoveLeftActionComponent.h"
#include "MoveRightActionComponent.h"
#include "JumpActionComponent.h"
#include "PolyLineBodyComponent.h"
#include "DrawingSystem.h"
#include "BoxBodyComponent.h"
#include "PolygonBodyComponent.h"

#include <sstream>

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(150, 220, 255, 255)))
	{
		return false;
	}
	
	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	
	_inputSystem = KeyboardInputSystem::create(this);
	_inputSystem->retain();

	_collisionResolutionSystem = CollisionResolutionSystem::create(this);
	_collisionResolutionSystem->retain();

	_transformSystem = TransformSystem::create(this);
	_transformSystem->retain();

	_actionSystem = ActionSystem::create(this);
	_actionSystem->retain();

	_physicsSystem = PhysicsSystem::create(this);
	_physicsSystem->retain();

	_drawingSystem = DrawingSystem::create(this);
	_drawingSystem->retain();

	createGameScreen();
	
	//create main loop
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::update));

	return true;
}

void GameScene::createCollisionObjectsFromMap(TMXTiledMap* map)
{
	TMXObjectGroup* collisionObjectGroup = nullptr;
	if (collisionObjectGroup = map->getObjectGroup("CollisionObjects"))
	{
		GameEntity* levelCollisionEntity = nullptr;
		int entityIndex = 0;

		for (auto& object : collisionObjectGroup->getObjects())
		{
			// Creating the dummy collision entity
			levelCollisionEntity = GameEntity::create();
			std::ostringstream oss;
			oss << "levelCollisionEntity" << entityIndex;
			levelCollisionEntity->setName(oss.str());
			entityIndex++;

			// Debug component to show its bounds
			DebugNodeComponent* dnc = DebugNodeComponent::create();
			levelCollisionEntity->addComponent(dnc);

			// Read current collision object infos from the map and create physics body components
			float objectX = object.asValueMap().at("x").asFloat();
			float objectY = object.asValueMap().at("y").asFloat();

			TransformComponent* tc = TransformComponent::create();
			tc->setNextPosition(Vec2(objectX, objectY));
			levelCollisionEntity->addComponent(tc);

			if (object.asValueMap().find("points") == object.asValueMap().end())
			{
				// The object is a rectangle
				// Creating the box body component
				BoxBodyComponent* rbc = BoxBodyComponent::create();
				rbc->setRect(Rect(0, 0, object.asValueMap().at("width").asFloat(),
										object.asValueMap().at("height").asFloat()));
				levelCollisionEntity->addComponent(rbc);
			}
			//else
			//{
			//	// The object is a polygon
			//	// Creating the polygon body component

			//	// Array to store polygon points
			//	int nbPoints = object.asValueMap().at("points").asValueVector().size();
			//	Vec2* listPoints = new Vec2[nbPoints];
			//	int i = 0;
			//	for (auto& point : object.asValueMap().at("points").asValueVector())
			//	{
			//		// convert the points' local coordinates to the world coordinates
			//		// by doing a translation using the object's position vector

			//		// We invert the local y because it's based on the top-left space in Tiled
			//		listPoints[i].x = point.asValueMap().at("x").asInt();
			//		listPoints[i].y = -point.asValueMap().at("y").asInt();
			//		i++;
			//	}

			//	PolygonBodyComponent* pbc = PolygonBodyComponent::create();
			//	pbc->setPoints(listPoints, nbPoints);
			//	levelCollisionEntity->addComponent(pbc);
			//}

			addChild(levelCollisionEntity);
		}
	}
}

void GameScene::createGameScreen()
{
	GameEntity* level1 = GameEntity::create();
	level1->setName("Level1");

	TiledMapComponent* tmc = TiledMapComponent::create();
	tmc->setTMXFile("level1.tmx");
	level1->addComponent(tmc);

	TransformComponent* t1 = TransformComponent::create();
	level1->addComponent(t1);

	addChild(level1);

	// Creating collision objects to be used by the collision resolution system
	createCollisionObjectsFromMap(tmc->getTMXTiledMap());
	
	GameEntity* sona = GameEntity::create();
	sona->setName("Sona");

	SpriteComponent* sc = SpriteComponent::create();
	sc->setSpriteFile("sona.png");
	sona->addComponent(sc);

	TransformComponent* t2 = TransformComponent::create();
	t2->setNextPosition(Vec2(tmc->getTMXTiledMap()->getTileSize().width * 2, tmc->getTMXTiledMap()->getTileSize().height * 4));
	sona->addComponent(t2);

	VelocityComponent* vc = VelocityComponent::create();
	sona->addComponent(vc);

	float scale = 50;

	PhysicsComponent* pc = PhysicsComponent::create();
	pc->setMaxSpeed(Vec2(scale * 8, scale * 12));
	pc->setGravity(10 * scale);
	pc->setDecX(14 * scale);
	sona->addComponent(pc);

	// Instanciating the Action Components
	MoveLeftActionComponent* mlc = MoveLeftActionComponent::create();
	mlc->setAcc(8 * scale);
	sona->addComponent(mlc);

	MoveRightActionComponent* mrc = MoveRightActionComponent::create();
	mrc->setAcc(8 * scale);
	sona->addComponent(mrc);

	JumpActionComponent* jc = JumpActionComponent::create();
	jc->setJumpStartSpeedY(9 * scale);
	sona->addComponent(jc);

	// Creating a polygon physics body
	PolyLineBodyComponent* polyLineBody = PolyLineBodyComponent::create();

	// Top of the head
	polyLineBody->addLine(Vec2(15, 128), Vec2(40, 128));

	// Bottom of the feet
	polyLineBody->addLine(Vec2(15, 0), Vec2(40, 0));

	// Left arm
	polyLineBody->addLine(Vec2(10, 32), Vec2(10, 96));

	// Right arm
	polyLineBody->addLine(Vec2(45, 32), Vec2(45, 96));

	sona->addComponent(polyLineBody);

	DebugNodeComponent* debugNode = DebugNodeComponent::create();
	sona->addComponent(debugNode);

	addChild(sona);

	// Instanciating the Input Components
	KeyboardInputComponent* ic = KeyboardInputComponent::create();
	ic->mapActionToKey("MoveLeftAction", EventKeyboard::KeyCode::KEY_LEFT_ARROW);
	ic->mapActionToKey("MoveRightAction", EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	ic->mapActionToKey("JumpAction", EventKeyboard::KeyCode::KEY_SPACE);

	addComponent(ic);
}

void GameScene::update(float dt)
{
	//system("cls");
	_collisionResolutionSystem->update(dt);
	_transformSystem->update(dt);
	_actionSystem->update(dt);
	_physicsSystem->update(dt);
}

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	LayerColor::draw(renderer, transform, flags);
	_drawingSystem->draw();
}
