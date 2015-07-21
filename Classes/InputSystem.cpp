#include "InputSystem.h"
#include "InputComponent.h"

USING_NS_CC;

InputSystem::~InputSystem()
{
	// Stop listening to keyboard events
	Director::getInstance()->getEventDispatcher()->removeEventListener(_keyboardListener);

	CC_SAFE_RELEASE(_keyboardListener);
}

bool InputSystem::init(Node* owner)
{
	// Register keyboard event handlers
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(InputSystem::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(InputSystem::onKeyReleased, this);
	_keyboardListener->retain();

	// Start listening to keyboard events
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(_keyboardListener, owner);

	return true;
}

void InputSystem::registerComponent(InputComponent* c)
{
	_components.pushBack(c);
}

void InputSystem::unregisterComponent(InputComponent* c)
{
	_components.eraseObject(c, true);
}

void InputSystem::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// Loop through all observing components and update their key maps
	for (InputComponent* component : _components)
	{
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		if (component->_keys.find(keyCode) == component->_keys.end()){
			component->_keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
	}
}

void InputSystem::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// Loop through all observing components and update their key maps
	for (InputComponent* component : _components)
	{
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		component->_keys.erase(keyCode);
	}
}
