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

	_actionSystem = ActionSystem::create();
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
	
	_sona = GameEntity::create();
	_sona->setName("Sona");
	_sona->retain();

	SpriteComponent* sc = SpriteComponent::create();
	sc->setSpriteFile("sona.png");
	_sona->addComponent(sc);

	TransformComponent* tc = TransformComponent::create();
	tc->setPos(Vec2(_level->getTileSize().width * 2, _level->getTileSize().height * 4));
	_sona->addComponent(tc);

	VelocityComponent* vc = VelocityComponent::create();
	_sona->addComponent(vc);

	PhysicsComponent* pc = PhysicsComponent::create();
	pc->setMaxSpeed(Vec2(400, 600));
	pc->setGravity(30);
	pc->setDecX(800);
	_sona->addComponent(pc);

	// Instanciating the Action Components
	MoveLeftActionComponent* mlc = MoveLeftActionComponent::create();
	mlc->setAcc(800);
	_sona->addComponent(mlc);

	MoveRightActionComponent* mrc = MoveRightActionComponent::create();
	mrc->setAcc(800);
	_sona->addComponent(mrc);

	JumpActionComponent* jc = JumpActionComponent::create();
	jc->setJumpStartSpeedY(750);
	_sona->addComponent(jc);

	// Instanciating the Input Components
	KeyboardInputComponent* ic = KeyboardInputComponent::create();
	ic->mapActionToKey(ActionType::MoveLeft, EventKeyboard::KeyCode::KEY_LEFT_ARROW);
	ic->registerAction(ActionType::MoveLeft, mlc);

	ic->mapActionToKey(ActionType::MoveRight, EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	ic->registerAction(ActionType::MoveRight, mrc);

	ic->mapActionToKey(ActionType::Jump, EventKeyboard::KeyCode::KEY_SPACE);
	ic->registerAction(ActionType::Jump, jc);

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
