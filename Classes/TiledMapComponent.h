#ifndef __TILED_MAP_COMPONENT_H__
#define __TILED_MAP_COMPONENT_H__

#include "cocos2d.h"

class TiledMapComponent : public cocos2d::Component
{
public:
	CREATE_FUNC(TiledMapComponent);

	virtual ~TiledMapComponent();

	virtual bool init();

	virtual void setTMXFile(std::string file);

	CC_SYNTHESIZE(cocos2d::TMXTiledMap*, _tmxTiledMap, TMXTiledMap);
};

#endif // __TILED_MAP_COMPONENT_H__