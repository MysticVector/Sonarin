#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "cocos2d.h"

class KeyboardInputSystem : public cocos2d::Ref
{
public:
	static KeyboardInputSystem* create(cocos2d::Node* owner);

	virtual ~KeyboardInputSystem();

	virtual bool init(cocos2d::Node* owner);

private:
	// Cocos2D-X's keyboard event handlers
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	// Cocos2D-X's keyboard listener
	cocos2d::EventListenerKeyboard* _keyboardListener;

	cocos2d::Node* _owner;
};

#endif // __INPUT_SYSTEM_H__