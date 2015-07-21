#include "InputComponent.h"

USING_NS_CC;

void InputComponent::mapAction(InputAction action, cocos2d::EventKeyboard::KeyCode key)
{
	_keysByAction[action] = key;
	//_actionsByKey[key] = action;
}

void InputComponent::unmapAction(InputAction action)
{
	if (_keysByAction.find(action) != _keysByAction.end())
	{
		// Look for the key corresponding to the unmapped action
		//EventKeyboard::KeyCode key = _keysByAction[action];

		// update both maps
		_keysByAction.erase(action);
		//_actionsByKey.erase(key);
	}
}


bool InputComponent::isActionPressed(InputAction action) const
{	
	// Check if the key is mapped first
	if (_keysByAction.find(action) == _keysByAction.end())
		return false;

	// Get the key mapped to this action
	EventKeyboard::KeyCode key = _keysByAction.find(action)->second;
	
	// Check if the key is currently pressed by seeing if it's in the std::map keys
	if (_keys.find(key) != _keys.end())
		return true;

	return false;
}

double InputComponent::actionPressedDuration(InputAction action) const
{
	// Check if the key is mapped first
	if (_keysByAction.find(action) == _keysByAction.end())
		return 0;

	// Get the key mapped to this action
	EventKeyboard::KeyCode key = _keysByAction.find(action)->second;

	// Return the amount of time that has elapsed between now and when the user
	// first started holding down the key in milliseconds
	// Obviously the start time is the value we hold in our std::map keys
	if (_keys.find(key) != _keys.end())
		return std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::high_resolution_clock::now() - _keys.find(key)->second).count();

	return 0;
}