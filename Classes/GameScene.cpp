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

void GameScene::createGameScreen()
{
	GameEntity* level1 = GameEntity::create();
	level1->setName("Level1");

	TiledMapComponent* tmc = TiledMapComponent::create();
	tmc->setTMXFile("level1.tmx");
	level1->addComponent(tmc);

	TransformComponent* t1 = TransformComponent::create();
	level1->addComponent(t1);

	//_level = Level::create("level1.tmx", "Static_Shapes");

	addChild(level1);
	
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
	polyLineBody->addPoint(Vec2(15, 128));
	polyLineBody->addPoint(Vec2(40, 128));

	// Bottom of the feet
	polyLineBody->addPoint(Vec2(15, 0));
	polyLineBody->addPoint(Vec2(40, 0));

	// Left arm
	polyLineBody->addPoint(Vec2(10, 32));
	polyLineBody->addPoint(Vec2(10, 96));

	// Right arm
	polyLineBody->addPoint(Vec2(45, 32));
	polyLineBody->addPoint(Vec2(45, 96));

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
