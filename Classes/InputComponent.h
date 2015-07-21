#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "cocos2d.h"

enum InputAction
{
	MoveLeft,
	MoveRight,
	Jump
};

class InputComponent : public cocos2d::Component
{
	friend class InputSystem;

public:
	InputComponent() { _name = "Input"; }
	virtual ~InputComponent() {}

	// Maps a new action to a key (ex: MoveLeft => KEY_LEFT)
	void mapAction(InputAction action, cocos2d::EventKeyboard::KeyCode key);
	void unmapAction(InputAction action);

	// From the outside we don't interact with keys, only actions are used
	// That enables changing the keys to whatever the player wants
	bool isActionPressed(InputAction action) const;
	double actionPressedDuration(InputAction action) const;
	
private:
	// A map that tracks the state of the pressed keys
	std::unordered_map<cocos2d::EventKeyboard::KeyCode, 
		std::chrono::high_resolution_clock::time_point> _keys;

	// Maps that link a key to an action in game, we have 2 maps in order to permit
	// a search using either a key or an action
	std::unordered_map<InputAction, cocos2d::EventKeyboard::KeyCode> _keysByAction;
	//std::unordered_map<cocos2d::EventKeyboard::KeyCode, InputAction> _actionsByKey;
};

#endif // __INPUT_COMPONENT_H__