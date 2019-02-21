#pragma region include

#pragma once
#include "stdafx.h"

#include "InputActions.h"
#include "ControllerMapping.h"

using namespace std;
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


	bool isButtonDown(const ControllerButtonMapping buttonIdx, const int playerIdx);
	bool isButtonUp(const ControllerButtonMapping buttonIdx, const int playerIdx);
	bool isButtonPressed(const ControllerButtonMapping buttonIdx, const int playerIdx);
	bool isButtonReleased(const ControllerButtonMapping buttonIdx, const int playerIdx);
	bool isStickPushed(const ControllerStickMapping stickIdx, const int playerIdx);

	bool isButtonDown(const InputActions action, const int playerIdx);
	bool isButtonUp(const InputActions action, const int playerIdx);
	bool isButtonPressed(const InputActions action, const int playerIdx);
	bool isButtonReleased(const InputActions action, const int playerIdx);
	bool isStickPushed(const InputActions action, const int playerIdx);

	bool isActionActive(const InputActions action, const int playerIdx);

	bool unbind(const InputActions action, const int playerIndex);

	bool bind(const InputActions action, const Keyboard::Key keyCode, const int playerIndex);
	bool bind(const InputActions action, const ControllerButtonMapping buttonCode, const int playerIndex);
	bool bind(const InputActions action, const ControllerStickMapping stickCode, const int playerIndex);

private:
	InputManager(void) = default;
	~InputManager(void) = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator=(InputManager const&) = delete;

	vector<map<const InputActions, const Keyboard::Key>> m_keyBindings;
	map<Keyboard::Key, bool> m_wasKeyDownLastFrame;

	//Controller
	vector<map<const InputActions, const ControllerButtonMapping>> m_buttonBindings;
	vector<map<const InputActions, const ControllerStickMapping>> m_stickBindings;
	vector<map<ControllerButtonMapping, bool>> m_wasButtonDownLastFrame;
};
