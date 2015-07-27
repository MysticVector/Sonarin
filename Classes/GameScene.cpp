#include "GameScene.h"
#include "GameEntity.h"
#include "SpriteComponent.h"
#include "TranformComponent.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "KeyboardInputComponent.h"
#include "KeyboardInputSystem.h"
#include "ActionSystem.h"
#include "ActionComponent.h"
#include "MoveLeftActionComponent.h"
#include "MoveRightActionComponent.h"
#include "JumpActionComponent.h"

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
	
	_inputSystem = new KeyboardInputSystem();
	_inputSystem->init(this);
	_inputSystem->retain();

	_actionSystem = new ActionSystem();
	_actionSystem->retain();

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

	VelocityComponent* vc = new VelocityComponent();
	vc->autorelease();
	_sona->addComponent(vc);

	PhysicsComponent* pc = new PhysicsComponent();
	pc->init(Vec2(400, 600), 30, 800);
	vc->autorelease();
	_sona->addComponent(pc);

	// Instanciating the Action Components
	MoveLeftActionComponent* mlc = new MoveLeftActionComponent();
	mlc->init(800);
	mlc->autorelease();
	_sona->addComponent(mlc);

	MoveRightActionComponent* mrc = new MoveRightActionComponent();
	mrc->init(800);
	mrc->autorelease();
	_sona->addComponent(mrc);

	JumpActionComponent* jc = new JumpActionComponent();
	jc->init(750);
	jc->autorelease();
	_sona->addComponent(jc);

	// Instanciating the Input Components
	KeyboardInputComponent* ic = new KeyboardInputComponent();
	ic->mapActionToKey(ActionType::MoveLeft, EventKeyboard::KeyCode::KEY_LEFT_ARROW);
	ic->registerAction(ActionType::MoveLeft, mlc);

	ic->mapActionToKey(ActionType::MoveRight, EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	ic->registerAction(ActionType::MoveRight, mrc);

	ic->mapActionToKey(ActionType::Jump, EventKeyboard::KeyCode::KEY_SPACE);
	ic->registerAction(ActionType::Jump, jc);

	ic->autorelease();
	_inputSystem->registerComponent(ic);
	_sona->addComponent(ic);

	_actionSystem->registerEntity(_sona);
	addChild(_sona);
}

void GameScene::update(float dt)
{
	//system("cls");
	_actionSystem->update(dt);
}
