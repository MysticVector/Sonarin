#ifndef __TILED_MAP_COMPONENT_H__
#define __TILED_MAP_COMPONENT_H__

#include "cocos2d.h"

class TiledMapComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(TiledMapComponent);

	virtual ~TiledMapComponent() {	CC_SAFE_RELEASE(_tmxTiledMap);	}

	virtual bool init()
	{
		_name = "TiledMap";
		_tmxTiledMap = nullptr;
		return true;
	}

	virtual void setTMXFile(std::string file)
	{
		CC_SAFE_RELEASE(_tmxTiledMap);
		_tmxTiledMap = cocos2d::TMXTiledMap::create(file);
		_tmxTiledMap->setAnchorPoint(cocos2d::Vec2(0, 0));
		CC_SAFE_RETAIN(_tmxTiledMap);
		assert(_tmxTiledMap);
	}

	CC_SYNTHESIZE(cocos2d::TMXTiledMap*, _tmxTiledMap, TMXTiledMap);
};

#endif // __TILED_MAP_COMPONENT_H__