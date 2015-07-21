#include "GameScene.h"
#include "GameEntity.h"
#include "SpriteComponent.h"
#include "TranformComponent.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "InputSystem.h"
#include "MovementSystem.h"

USING_NS_CC;

GameScene::~GameScene()
{
}


Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
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
	
	_inputSystem = new InputSystem();
	_inputSystem->init(this);
	_inputSystem->retain();

	_movementSystem = new MovementSystem();
	_movementSystem->retain();

	createGameScreen();
	
	//create main loop
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::update));

	return true;
}

void GameScene::createGameScreen()
{
	_level = Level::create("level1.tmx", "Static_Shapes");
	addChild(_level);
	
	_sona = new GameEntity();
	_sona->retain();
	_sona->setName("Sona");

	SpriteComponent* sc = new SpriteComponent();
	sc->init(_sona, "sona.png");
	sc->autorelease();
	_sona->addComponent(sc);

	TransformComponent* tc = new TransformComponent();
	tc->pos = Vec2(_level->getTileSize().width * 2, _level->getTileSize().height * 4);
	tc->autorelease();
	_sona->addComponent(tc);

	MovementComponent* mc = new MovementComponent();
	mc->init(Vec2::ZERO, Vec2(400, 600), Vec2(800, 30), 800, 750);
	mc->autorelease();
	_sona->addComponent(mc);

	InputComponent* ic = new InputComponent();
	ic->mapAction(MoveLeft, EventKeyboard::KeyCode::KEY_LEFT_ARROW);
	ic->mapAction(MoveRight, EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	ic->mapAction(Jump, EventKeyboard::KeyCode::KEY_SPACE);
	ic->autorelease();
	_inputSystem->registerComponent(ic);
	_sona->addComponent(ic);

	_movementSystem->registerEntity(_sona);
	addChild(_sona);
}

void GameScene::update(float dt)
{
	//system("cls");
	_movementSystem->update(dt);
}
