#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "ActionComponent.h"

class KeyboardInputComponent : public cocos2d::Component
{
	friend class KeyboardInputSystem;
public:
	CREATE_FUNC(KeyboardInputComponent);

	virtual bool init()
	{
		_name = "KeyboardInput";
		return true;
	}

	// Maps new actions to a key (ex: MoveLeft => KEY_LEFT)
	static void mapActionToKey(std::string action, cocos2d::EventKeyboard::KeyCode key);
	static void unmapActionFromKey(cocos2d::EventKeyboard::KeyCode key);
	
private:
	// A map that links a key to an ActionType in game
	static std::unordered_map<cocos2d::EventKeyboard::KeyCode, std::string> _actionsByKey;
};

#endif // __INPUT_COMPONENT_H__