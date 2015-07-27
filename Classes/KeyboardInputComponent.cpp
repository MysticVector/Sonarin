#include "KeyboardInputComponent.h"

USING_NS_CC;


void KeyboardInputComponent::registerAction(ActionType at, ActionComponent* action)
{
	_actions[at] = action;
}

void KeyboardInputComponent::unregisterAction(ActionType at)
{
	if (_actions.find(at) != _actions.end())
	{
		_actions.erase(at);
	}
}

void KeyboardInputComponent::mapActionToKey(ActionType at, EventKeyboard::KeyCode key)
{
	_actionsByKey[key] = at;
}

void KeyboardInputComponent::unmapActionFromKey(EventKeyboard::KeyCode key)
{
	if (_actionsByKey.find(key) != _actionsByKey.end())
	{
		_actionsByKey.erase(key);
	}
}