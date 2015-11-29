#include "KeyboardInputSystem.h"
#include "KeyboardInputComponent.h"

USING_NS_CC;

std::unordered_map<cocos2d::EventKeyboard::KeyCode, std::string> KeyboardInputComponent::_actionsByKey;

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
	_owner = owner;

	// Register keyboard event handlers
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardInputSystem::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(KeyboardInputSystem::onKeyReleased, this);
	_keyboardListener->retain();

	// Start listening to keyboard events
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, owner);

	return true;
}

void KeyboardInputSystem::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	KeyboardInputComponent* inputComponent = nullptr;
	
	if (inputComponent = static_cast<KeyboardInputComponent*>(_owner->getComponent("KeyboardInput")))
	{
		// Checking whether the key is mapped to an action in game
		if (KeyboardInputComponent::_actionsByKey.find(keyCode) != KeyboardInputComponent::_actionsByKey.end())
		{
			Vector<Node*> entities = _owner->getChildren();
			ActionComponent* actionComponent = nullptr;

			for (Node* entity : entities)
			{
				if (actionComponent = static_cast<ActionComponent*>(entity->getComponent(KeyboardInputComponent::_actionsByKey[keyCode])))
				{
					actionComponent->setActive(true);
				}
			}
		}
	}
}

void KeyboardInputSystem::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	KeyboardInputComponent* inputComponent = nullptr;
	
	if (inputComponent = static_cast<KeyboardInputComponent*>(_owner->getComponent("KeyboardInput")))
	{
		// Checking whether the key is mapped to an action in game
		if (KeyboardInputComponent::_actionsByKey.find(keyCode) != KeyboardInputComponent::_actionsByKey.end())
		{
			Vector<Node*> entities = _owner->getChildren();
			ActionComponent* actionComponent = nullptr;

			for (Node* entity : entities)
			{
				if (actionComponent = static_cast<ActionComponent*>(entity->getComponent(KeyboardInputComponent::_actionsByKey[keyCode])))
				{
					actionComponent->setActive(false);
				}
			}
		}
	}
}
