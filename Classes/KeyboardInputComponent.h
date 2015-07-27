#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"


enum ActionType
{
	MoveLeft,
	MoveRight,
	Jump
};

class KeyboardInputComponent : public cocos2d::Component
{
	friend class KeyboardInputSystem;

public:
	KeyboardInputComponent() { _name = "Input"; }
	virtual ~KeyboardInputComponent() {}

	void registerAction(ActionType at, ActionComponent* action);
	void unregisterAction(ActionType at);

	// Maps new actions to a key (ex: MoveLeft => KEY_LEFT)
	static void mapActionToKey(ActionType at, cocos2d::EventKeyboard::KeyCode key);
	static void unmapActionFromKey(cocos2d::EventKeyboard::KeyCode key);
	
private:
	// A map that links a key to an ActionType in game
	static std::unordered_map<cocos2d::EventKeyboard::KeyCode, ActionType> _actionsByKey;

	// Mapping the ActionComponents that describe what each entity does (does it moveLeft ? does it Jump ?) 
	// to the keyboardActions that describe what are the controls that are possible
	// this is updated whenever we add or remove an ActionComponent
	std::unordered_map<ActionType, ActionComponent*> _actions;
};

#endif // __INPUT_COMPONENT_H__