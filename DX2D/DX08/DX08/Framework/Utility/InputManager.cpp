#include "framework.h"
#include "InputManager.h"

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager()
: _state{}
, _oldState{}
, _stateMap{}
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(_oldState, _state, sizeof(_oldState));

	GetKeyboardState(_state);
	
	for (int i = 0; i < KEY_MAX; i++)
	{
		byte key = _state[i] & 0x80;
		_state[i] = key ? 1 : 0; // 삼항 연산자, key 가 true이면 1, false 이면 0

		int old = _oldState[i];
		int cur = _state[i];

		if (old == 0 && cur == 1)
		{
			_stateMap[i] = State::DOWN;
		}
		else if (old == 1 && cur == 0)
		{
			_stateMap[i] = State::UP;
		}
		else if (old == 1 && cur == 1)
		{
			_stateMap[i] = State::PRESS;
		}
		else
		{
			_stateMap[i] = State::NONE;
		}
	}
}
