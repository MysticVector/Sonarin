#include "KeyboardInputSystem.h"
#include "KeyboardInputComponent.h"

USING_NS_CC;

std::unordered_map<cocos2d::EventKeyboard::KeyCode, ActionType> KeyboardInputComponent::_actionsByKey;

KeyboardInputSystem* KeyboardInputSystem::create(cocos2d::Node* owner)
{
	KeyboardInputSystem * ret = new (std::nothrow) KeyboardInputSystem();
	if (ret != nullptr && ret->init(owner))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

KeyboardInputSystem::~KeyboardInputSystem()
{
	// Stop listening to keyboard events
	Director::getInstance()->getEventDispatcher()->removeEventListener(_keyboardListener);

	CC_SAFE_RELEASE(_keyboardListener);
}

bool KeyboardInputSystem::init(Node* owner)
{
	// Register keyboard event handlers
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardInputSystem::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(KeyboardInputSystem::onKeyReleased, this);
	_keyboardListener->retain();

	// Start listening to keyboard events
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(_keyboardListener, owner);

	return true;
}

void KeyboardInputSystem::registerComponent(KeyboardInputComponent* c)
{
	_components.pushBack(c);
}

void KeyboardInputSystem::unregisterComponent(KeyboardInputComponent* c)
{
	_components.eraseObject(c, true);
}

void KeyboardInputSystem::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	ActionType at;

	// Loop through all observing components and update their key maps
	for (KeyboardInputComponent* component : _components)
	{
		if (KeyboardInputComponent::_actionsByKey.find(keyCode) != 
						KeyboardInputComponent::_actionsByKey.end()){
			at = KeyboardInputComponent::_actionsByKey[keyCode];

			if (component->_actions.find(at) !=	component->_actions.end()){
				component->_actions[at]->_enabled = true;
			}
		}
	}
}

void KeyboardInputSystem::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	ActionType at;

	// Loop through all observing components and update their key maps
	for (KeyboardInputComponent* component : _components)
	{
		// Checking whether the key is mapped to an action in game
		if (KeyboardInputComponent::_actionsByKey.find(keyCode) !=
			KeyboardInputComponent::_actionsByKey.end()){
			at = KeyboardInputComponent::_actionsByKey[keyCode];

			// Checking if the ActionType has an ActionComponent bound to it, 
			// otherwise this is a coding mistake
			if (component->_actions.find(at) != component->_actions.end()){
				component->_actions[at]->_enabled = false;
			}
		}
	}
}
