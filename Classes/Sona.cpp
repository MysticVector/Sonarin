#include "Sona.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"

using namespace CocosDenshion;
using namespace cocostudio;

USING_NS_CC;

Sona::~Sona()
{
	CC_SAFE_RELEASE(_idleAnimation);
	CC_SAFE_RELEASE(_runAnimation);
}

Sona::Sona() 
	: c_gravity(0.0, -450.0), c_jumpForce(310), c_jumpCutOff(100),
	c_moveSpeed(800), c_minMovement(-120.0, -450.0), c_maxMovement(120.0, 250.0)
{
	_screenSize = CCDirector::getInstance()->getWinSize();

	_velocity = Point(0, 0);

	_movingRight = false;
	_movingLeft = false;
	_pressingJump = false;

	_direction = kSonaRight;
	_state = kSonaIdle;
}

Sona* Sona::create()
{
	Sona* player = new Sona();
	if (player && player->initWithSpriteFrameName("sona_idle1.png")) {
		player->autorelease();
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Sona::initPlayer()
{
	// TESTS
	//ArmatureDataManager::getInstance()->addArmatureFileInfo("Sona/Sona.ExportJson");
	//Armature* sonaArmature = Armature::create("Sona");
	//
	//getTexture()->generateMipmap();
	//Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, 
	//	GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
	//getTexture()->setTexParameters(texParams);
	//
	//addChild(sonaArmature);
	//sonaArmature->getAnimation()->playWithIndex(0);
	////sonaArmature->setScale(0.3f);
	//getTexture()->setAliasTexParameters();

	Animation* animation;
	SpriteFrame * frame;
	char szName[20] = { 0 };
	
	// Initializing the idle animation
	animation = Animation::create();
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("sona_idle1.png");
	animation->addSpriteFrame(frame);
	animation->setDelayPerUnit(1.0f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(0);
	_idleAnimation = Animate::create(animation);
	_idleAnimation->retain();

	// Initializing the run animation
	animation = Animation::create();
	for (int i = 1; i <= 8; i++) {
		sprintf(szName, "sona_run%i.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(1.0 / 15);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	_runAnimation = RepeatForever::create(Animate::create(animation));
	_runAnimation->retain();

	this->runAction(_idleAnimation);
}

void Sona::update(float dt)
{
	// Calculate sona's falling velocity
	_velocity += c_gravity * dt;
	if (abs(_velocity.y) > 10)
		log("0");

	// Calculate sona's jump velocity
	if (!_pressingJump && _velocity.y > c_jumpCutOff)
	{
		// if we stop jumping before reaching max jump height
		_velocity = Point(_velocity.x, c_jumpCutOff);
	}
	if (abs(_velocity.y) > 10)
		log("1");

	// Calculate sona's movement velocity
	float movement = 0.0;

	if (_movingRight)
	{
		movement += c_moveSpeed;
	}
	else if (_movingLeft)
	{
		movement -= c_moveSpeed;
	}
	else
	{
		// Applying a damping force to sona when she stops moving
		_velocity = Point(_velocity.x * 0.75, _velocity.y);
	}
	
	_velocity.x += movement * dt;

	// Appply min and max limits to the velocity
	_velocity = _velocity.getClampPoint(c_minMovement, c_maxMovement);

	if (abs(_velocity.y) > 10)
		log("2");
	
	// Apply final velocity to the next desired position
	_nextPosition = getPosition() + _velocity * dt;
	if (abs(_velocity.y) > 10)
		log("(%.2f, %.2f) (%.2f, %.2f)", _velocity.x, _velocity.y, _position.x, _position.y);

	if (_showDebug)
		drawDebug();
}

void Sona::reset()
{
	_velocity = Point(0, 0);

	_state = kSonaIdle;

	_position = _nextPosition;
}

void Sona::startMoveRight()
{
	setState(kSonaRunning);
	_movingRight = true;
}

void Sona::stopMoveRight()
{
	setState(kSonaIdle);
	_movingRight = false;
}

void Sona::startMoveLeft()
{
	setState(kSonaRunning);
	_movingLeft = true;
}

void Sona::stopMoveLeft()
{
	setState(kSonaIdle);
	_movingLeft = false;
}

void Sona::startJump()
{
	_pressingJump = true;

	if (_onGround)
	{
		_velocity.y += c_jumpForce;
	}
}

void Sona::stopJump()
{
	_pressingJump = false;
}

void Sona::setDirection(char direction)
{
	// If we're not setting both directions at once (buttons mashed together)
	// set the new direction
	if (direction != (kSonaRight | kSonaLeft))
		setScaleX(abs(getScaleX()) * (direction == kSonaRight ? 1 : -1));
	
	_direction = direction;
}

void Sona::setState(SonaState state)
{
	stopAllActions();
	switch (state)
	{
	case kSonaIdle:
		runAction(_idleAnimation);
		break;
	case kSonaRunning:
		runAction(_runAnimation);
		break;
	default:
		break;
	}

	_state = state;
}

void Sona::drawDebug()
{
	_debugNode->clear();

	Rect bb = getCollisionBoundingBox();
	_debugNode->drawRect(bb.origin, bb.origin + bb.size, Color4F::WHITE);
}