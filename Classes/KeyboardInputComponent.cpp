#include "KeyboardInputComponent.h"

USING_NS_CC;


void KeyboardInputComponent::mapActionToKey(std::string action, EventKeyboard::KeyCode key)
{
	_actionsByKey[key] = action;
}

void KeyboardInputComponent::unmapActionFromKey(EventKeyboard::KeyCode key)
{
	if (_actionsByKey.find(key) != _actionsByKey.end())
	{
		_actionsByKey.erase(key);
	}
}