#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Sona.h"

class GameScene : public cocos2d::LayerColor
{
private:
	cocos2d::Size _visibleSize;
	cocos2d::Point _origin;

	Sona* _sona;
	cocos2d::SpriteBatchNode * _gameBatchNode;

	cocos2d::TMXTiledMap *_map;
	cocos2d::TMXLayer *_walls;

	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

	void createGameScreen();

	cocos2d::Point tileCoordFromPosition(cocos2d::Point pos);
	cocos2d::Rect tileRectFromTileCoords(cocos2d::Point tileCoords);
	cocos2d::Vector<cocos2d::Dictionary*>* getSurroundingTilesAtPosition(cocos2d::Point pos, cocos2d::TMXLayer* layer);
	void GameScene::checkForAndResolveCollisions();

	cocos2d::Rect RectIntersection(const cocos2d::Rect & r1, const cocos2d::Rect & r2) const;

	void setViewportCenter(cocos2d::Point position);

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode keyCode);
	
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void update(float dt);
};

#endif // __GAMESCENE_H__
