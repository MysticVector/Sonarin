#ifndef __SONA_H__
#define __SONA_H__

#define SONA_MAX_SPEED 8
#define PLAYER_JUMP 42

#include "cocos2d.h"
#include "GameSprite.h"

typedef enum
{
	kSonaIdle,
	kSonaRunning,
} SonaState;


typedef enum
{
	kSonaRight = 1,
	kSonaLeft = 2,
} SonaDirection;

class Sona : public GameSprite
{
private:

	// the direction comprises of 2 flags that can be activated at the same time
	// the bit corresponding to 1s and the bit corresponding to 2s
	char _direction;
	SonaState _state;
	
	cocos2d::Rect _collisionBoundingBox;

	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _runAnimation;
	
	void initPlayer();

	void drawDebug();

public:
	const float c_moveSpeed;
	const float c_jumpForce;
	const float c_jumpCutOff;
	const cocos2d::Point c_gravity;
	const cocos2d::Point c_minMovement;
	const cocos2d::Point c_maxMovement;

	CC_SYNTHESIZE(bool, _movingRight, MovingRight);
	CC_SYNTHESIZE(bool, _movingLeft, MovingLeft);
	CC_SYNTHESIZE(bool, _pressingJump, PressingJump);
	CC_SYNTHESIZE(bool, _onGround, OnGround);


	Sona();
	~Sona();

	static Sona* create();
	virtual void update(float dt);
	void reset();

	void startMoveRight();
	void stopMoveRight();

	void startMoveLeft();
	void stopMoveLeft();

	void startJump();
	void stopJump();

	void setDirection(char direction);
	
	inline char getDirection() const
	{
		return _direction;
	}

	void setState(SonaState state);
	
	inline SonaState getState() const
	{
		return _state;
	}

	inline cocos2d::Rect getCollisionBoundingBox() 
	{
		// Return a smaller bounding box
		_collisionBoundingBox = cocos2d::Rect(getBoundingBox().origin.x + 10,
			getBoundingBox().origin.y + 1,
			getBoundingBox().size.width - 20,
			getBoundingBox().size.height - 2);

		_collisionBoundingBox.origin.add(_nextPosition - _position);
		return _collisionBoundingBox;
	}
};

#endif // __SONA_H__