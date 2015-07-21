#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "cocos2d.h"

class GameObject;
class InputComponent;

class InputSystem : public cocos2d::Ref
{
public:
	virtual ~InputSystem();

	virtual bool init(cocos2d::Node* owner);

	// Methods to handle the observing components (Observer Pattern)
	void registerComponent(InputComponent* c);
	void unregisterComponent(InputComponent* c);

private:
	// Cocos2D-X's keyboard event handlers
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// List of observing components
	cocos2d::Vector<InputComponent*> _components;

	// Cocos2D-X's keyboard listener
	cocos2d::EventListenerKeyboard* _keyboardListener;
};

#endif // __INPUT_SYSTEM_H__