#include "GameScene.h"

USING_NS_CC;

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameScene::keys;

GameScene::~GameScene()
{
	delete _moveRightCommand;
	delete _moveLeftCommand;
}


Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// Show the bounding boxes around all physics objects
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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
	
	_moveRightCommand = new MoveCommand(Vec2(1000, 0));
	_moveLeftCommand = new MoveCommand(Vec2(-1000, 0));
	
	createGameScreen();

	// Listen to keyboard events
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	//create main loop
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::update));

	return true;
}

void GameScene::createGameScreen()
{
	_level = Level::create("level1.tmx", "Static_Shapes");
	addChild(_level);
	
	// Load the player sprite definition file
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sona_idle.plist", "sona_idle.png");

	// Create the player object
	_sona = Sona::create();
	_sona->setPosition(Vec2(_level->getTileSize().width * 2, _level->getTileSize().height * 5));
	_level->addChild(_sona, 10);
}

void GameScene::update(float dt)
{
	_sona->update(dt);
	_level->update(dt);

	Command* cmd = handleInput();
	if (cmd)
	{
		cmd->execute(_sona);
	}
}

Command* GameScene::handleInput()
{
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		return _moveRightCommand;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		return _moveLeftCommand;
	}

	return NULL;
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// If a key already exists, do nothing as it will already have a time stamp
	// Otherwise, set's the timestamp to now
	if (keys.find(keyCode) == keys.end()){
		keys[keyCode] = std::chrono::high_resolution_clock::now();
	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// remove the key.  std::map.erase() doesn't care if the key doesnt exist
	keys.erase(keyCode);
}

bool GameScene::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

double GameScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
		return 0;  // Not pressed, so no duration obviously

	// Return the amount of time that has elapsed between now and when the user
	// first started holding down the key in milliseconds
	// Obviously the start time is the value we hold in our std::map keys
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - keys[code]).count();
}