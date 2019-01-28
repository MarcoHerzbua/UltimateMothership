#pragma region include

#pragma once
#include "stdafx.h"

// enums
#include "InputActions.h"

// using
using namespace sf;

#pragma endregion


class InputManager
{
public:
	static InputManager& getInstance();

	void update();

	bool isKeyDown(const Keyboard::Key keyCode);
	bool isKeyUp(const Keyboard::Key keyCode);
	bool isKeyPressed(const Keyboard::Key keyCode);
	bool isKeyReleased(const Keyboard::Key keyCode);
	
	bool isKeyDown(const InputActions action, const int playerIndex);
	bool isKeyUp(const InputActions action, const int playerIndex);
	bool isKeyPressed(const InputActions action, const int playerIndex);
	bool isKeyReleased(const InputActions action, const int playerIndex);

	bool bind(const InputActions action, const Keyboard::Key keyCode, const int playerIndex);
	bool unbind(const InputActions action, const int playerIndex);

private:
	InputManager(void) = default;
	~InputManager(void) = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator=(InputManager const&) = delete;

	std::vector<std::map<const InputActions, const Keyboard::Key>> m_keyBindings;
	std::map<Keyboard::Key, bool> m_wasKeyDownLastFrame;
};
