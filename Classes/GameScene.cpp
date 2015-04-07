#include "GameScene.h"

USING_NS_CC;

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameScene::keys;

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
	
	_showDebug = false;
	_debugNode = DrawNode::create();

	createGameScreen();

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
	//// add background image
	//auto sprite = Sprite::create("background.png");
	//// position the sprite on the center of the screen
	//sprite->setPosition(Point(_visibleSize.width * 0.5f + _origin.x, _visibleSize.height * 0.5f + _origin.y));
	//// add the sprite as a child to this layer
	//this->addChild(sprite, kBackground);

	_map = TMXTiledMap::create("level1.tmx");
	addChild(_map);

	_immovableLayer = _map->layerNamed("Immovable");

	// Load the player sprite definition file
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sona_idle.plist", "sona_idle.png");

	// Create the player object
	_sona = Sona::create();
	_sona->setScale(0.60f);
	_sona->setPosition(Point(_map->getTileSize().width * 4, _map->getTileSize().height * 4));
	_map->addChild(_sona, 15);

	/*setShowDebug(true);
	_map->addChild(_debugNode, 20);

	_sona->setShowDebug(true);
	_map->addChild(_sona->getDebugNode(), 21);*/
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// If a key already exists, do nothing as it will already have a time stamp
	// Otherwise, set's the timestamp to now
	if (keys.find(keyCode) == keys.end()){
		keys[keyCode] = std::chrono::high_resolution_clock::now();
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_sona->getState() == kSonaRunning)
		{
			_sona->stopMoveLeft();
			_sona->setDirection(_sona->getDirection() | kSonaRight);
		}
		else
		{
			_sona->startMoveRight();
			_sona->setDirection(kSonaRight);
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_sona->getState() == kSonaRunning)
		{
			_sona->stopMoveRight();
			_sona->setDirection(_sona->getDirection() | kSonaLeft);
		}
		else
		{
			_sona->startMoveLeft();
			_sona->setDirection(kSonaLeft);
		}
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:		
		_sona->startJump();
		break;
	default:
		break;
	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// remove the key.  std::map.erase() doesn't care if the key doesnt exist
	keys.erase(keyCode);

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_sona->getState() == kSonaIdle && _sona->getDirection() == (kSonaLeft | kSonaRight))
		{
			_sona->startMoveLeft();
			_sona->setDirection(kSonaLeft);
		}
		else
		{
			_sona->stopMoveRight();
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_sona->getState() == kSonaIdle && _sona->getDirection() == (kSonaLeft | kSonaRight))
		{
			_sona->startMoveRight();
			_sona->setDirection(kSonaRight);
		}
		else
		{
			_sona->stopMoveLeft();
		}
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		_sona->stopJump();
		break;
	default:
		break;
	}
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

void GameScene::update(float dt)
{
	_sona->update(dt);

	checkForAndResolveCollisions();
	
	_sona->setPosition(_sona->getNextPosition());

	setViewportCenter(_sona->getPosition());
}

Point GameScene::tileCoordFromPosition(Point pos)
{
	float x = floor(pos.x / _map->getTileSize().width);
	float levelHeightinPixels = _map->getMapSize().height * _map->getTileSize().height;
	float y = floor((levelHeightinPixels - pos.y) / _map->getTileSize().height);
	return Point(x, y);
}

Rect GameScene::tileRectFromTileCoords(Point tileCoords)
{
	float levelHeightInPixels = _map->getMapSize().height * _map->getTileSize().height;
	Point origin = Point(tileCoords.x * _map->getTileSize().width, 
					   levelHeightInPixels - ((tileCoords.y + 1) * _map->getTileSize().height));
	return Rect(origin.x, origin.y, _map->getTileSize().width, _map->getTileSize().height);
}

Vector<Dictionary*>* GameScene::getSurroundingTilesAtPosition(Point pos, TMXLayer* layer)
{
	Point plPos = tileCoordFromPosition(pos);

	Vector<Dictionary*>* gids = new cocos2d::Vector<Dictionary*>();

	for (int i = 0; i < 9; i++)
	{
		int c = i % 3;
		int r = (int)(i / 3);
		Point tilePos = Point(plPos.x + (c - 1), plPos.y + (r - 1));

		int tgid = 0;

		if (tilePos.x >= 0 && tilePos.x < _map->getMapSize().width &&
			tilePos.y >= 0 && tilePos.y < _map->getMapSize().height)
		{
			tgid = layer->tileGIDAt(tilePos);
		}

		Rect tileRect = tileRectFromTileCoords(tilePos);

		Dictionary* tileDict = Dictionary::create();
		tileDict->setObject(Integer::create(tgid), "gid");
		tileDict->setObject(Float::create(tileRect.origin.x), "tileRectX");
		tileDict->setObject(Float::create(tileRect.origin.y), "tileRectY");
		tileDict->setObject(Float::create(tilePos.x), "tilePosX");
		tileDict->setObject(Float::create(tilePos.y), "tilePosY");

		gids->pushBack(tileDict);
	}

	gids->erase(4);
	gids->insert(6, gids->at(2));
	gids->erase(2);
	gids->swap(4, 6);
	gids->swap(0, 4);

	/*float x, y;

	for (Dictionary* d : *gids)
	{
		log("++++++++++");

		log("gid: %d", ((Integer*)d->objectForKey("gid"))->getValue());

		x = ((Float*)d->objectForKey("tileRectX"))->getValue();
		y = ((Float*)d->objectForKey("tileRectY"))->getValue();
		log("tileRect: (%.2f,%.2f)", x, y);

		x = ((Float*)d->objectForKey("tilePosX"))->getValue();
		y = ((Float*)d->objectForKey("tilePosY"))->getValue();
		log("tilePos: (%.2f,%.2f)", x, y);

		log("----------");
	}*/

	return gids;
}

void GameScene::checkForAndResolveCollisions()
{
	Vector<Dictionary*>* tiles = getSurroundingTilesAtPosition(_sona->getPosition(), _immovableLayer);

	if (_showDebug)
		drawDebug(tiles);

	_sona->setOnGround(false);

	Rect sonaBB = _sona->getCollisionBoundingBox();
	
	// Limit movement beyond the borders of the level
	if (_sona->getNextPosition().x < sonaBB.size.width * 0.5f)
	{
		_sona->setNextPosition(Point(sonaBB.size.width * 0.5f, _sona->getNextPosition().y));
	}
	else if (_sona->getNextPosition().x > (_map->getTileSize().width * _map->getMapSize().width) 
		- (_sona->getCollisionBoundingBox().size.width * 0.5f))
	{
		_sona->setNextPosition(Point((_map->getTileSize().width * _map->getMapSize().width) 
			- (_sona->getCollisionBoundingBox().size.width * 0.5f),
									_sona->getNextPosition().y));
	}

	for (Dictionary* d : *tiles)
	{
		sonaBB = _sona->getCollisionBoundingBox();

		int gid = ((Integer*)d->objectForKey("gid"))->getValue();

		if (gid)
		{
			Rect tileRect = Rect(((Float*)d->objectForKey("tileRectX"))->getValue(),
								 ((Float*)d->objectForKey("tileRectY"))->getValue(),
								 _map->getTileSize().width,
								 _map->getTileSize().height);

			if (sonaBB.intersectsRect(tileRect))
			{
				Rect intersection = RectIntersection(sonaBB, tileRect);

				int tileIndx = tiles->getIndex(d);

				switch (tileIndx)
				{
				case 0:
					// tile is directly below Sona
					_sona->setNextPosition(Point(_sona->getNextPosition().x,
						_sona->getNextPosition().y + intersection.size.height));
					_sona->setVelocity(Point(_sona->getVelocity().x, 0));
					_sona->setOnGround(true);
					break;
				case 1:
					// tile is directly above Sona
					_sona->setNextPosition(Point(_sona->getNextPosition().x,
						_sona->getNextPosition().y - intersection.size.height));
					_sona->setVelocity(Point(_sona->getVelocity().x, 0));
					break;
				case 2:
					// tile is left of Sona
					_sona->setNextPosition(Point(_sona->getNextPosition().x + intersection.size.width,
						_sona->getNextPosition().y));
					break;
				case 3:
					// tile is right of Sona
					_sona->setNextPosition(Point(_sona->getNextPosition().x - intersection.size.width,
						_sona->getNextPosition().y));
					break;
				default:
					if (intersection.size.width > intersection.size.height)
					{
						// tile is diagonal but resolving collision vertically
						//_sona->setVelocity(Point(_sona->getVelocity().x, 0));
						
						float intersectionHeight;
						if (tileIndx > 5)
						{
							intersectionHeight = intersection.size.height;
							_sona->setOnGround(true);
						}
						else
						{
							intersectionHeight = -intersection.size.height;
							_sona->setVelocity(Point(_sona->getVelocity().x, 0));
						}
						_sona->setNextPosition(Point(_sona->getNextPosition().x,
							_sona->getNextPosition().y + intersectionHeight));
					}
					else
					{
						//tile is diagonal, but resolving horizontally
						float resolutionWidth;
						if (tileIndx == 6 || tileIndx == 4)
						{
							resolutionWidth = intersection.size.width;
						}
						else
						{
							resolutionWidth = -intersection.size.width;
						}
						_sona->setNextPosition(Point(_sona->getNextPosition().x + resolutionWidth,
							_sona->getNextPosition().y));
					}
					break;
				}
			}
		}
	}
}

Rect GameScene::RectIntersection(const Rect & r1, const Rect & r2) const
{
	Rect r = Rect(std::max(r1.getMinX(), r2.getMinX()),
		std::max(r1.getMinY(), r2.getMinY()), 0, 0);
	r.size.width = std::min(r1.getMaxX(), r2.getMaxX()) - r.getMinX();
	r.size.height = std::min(r1.getMaxY(), r2.getMaxY()) - r.getMinY();
	return r;
}

void GameScene::setViewportCenter(Point position)
{
	int x = MAX(position.x, _visibleSize.width / 2);
	int y = MAX(position.y, _visibleSize.height / 2);

	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - _visibleSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - _visibleSize.height / 2);

	Point actualPosition = Point(x, y);
	Point centerOfView = Point(_visibleSize.width / 2, _visibleSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;

	_map->setPosition(viewPoint);
}


void GameScene::drawDebug(Vector<Dictionary*>* tiles)
{
	_debugNode->clear();

	for (Dictionary* d : *tiles)
	{
		Rect tileRect = Rect(((Float*)d->objectForKey("tileRectX"))->getValue(),
				((Float*)d->objectForKey("tileRectY"))->getValue(),
				_map->getTileSize().width,
				_map->getTileSize().height);

		_debugNode->drawRect(tileRect.origin, tileRect.origin + tileRect.size, Color4F::BLUE);
	}
}

//void GameScene::menuCloseCallback(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//	return;
//#endif
//
//	Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
//}
