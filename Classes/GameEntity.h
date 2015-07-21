#ifndef __GAMEENTITY_H__
#define __GAMEENTITY_H__

#include "cocos2d.h"

class GameEntity : public cocos2d::Node
{
public:
	GameEntity() { _name = "GameEntity"; }
	virtual ~GameEntity() {}
};

#endif // __GAMEENTITY_H__

