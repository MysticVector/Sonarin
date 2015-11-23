#include "TiledMapComponent.h"

USING_NS_CC;

TiledMapComponent::~TiledMapComponent()
{
	CC_SAFE_RELEASE(_tmxTiledMap);
}

bool TiledMapComponent::init()
{
	_name = "TiledMap";
	_tmxTiledMap = nullptr;
	return true;
}

void TiledMapComponent::setTMXFile(std::string file)
{
	_tmxTiledMap = TMXTiledMap::create(file);
	_tmxTiledMap->setAnchorPoint(Vec2(0, 0));
	assert(_tmxTiledMap);
	_tmxTiledMap->retain();
}