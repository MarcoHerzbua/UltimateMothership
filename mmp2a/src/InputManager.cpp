#pragma region include

#include "stdafx.h"
#include "InputManager.h"

#pragma endregion

void InputManager::update()
{
	for (auto pair : m_wasKeyDownLastFrame)
	{
		m_wasKeyDownLastFrame[pair.first] = isKeyDown(pair.first);
	}

	int playerIdx = 0;
	for (auto &map : m_wasButtonDownLastFrame)
	{
		for (auto &pair : map)
		{
			map[pair.first] = isButtonDown(pair.first, playerIdx);
		}
		playerIdx++;
	}

	//err() << m_wasButtonDownLastFrame[0][BUTTON_A];
}

bool InputManager::isKeyDown(const Keyboard::Key keyCode)
{
	return Keyboard::isKeyPressed(keyCode);
}

bool InputManager::isKeyUp(const Keyboard::Key keyCode)
{
	return !Keyboard::isKeyPressed(keyCode);
}

bool InputManager::isKeyPressed(const Keyboard::Key keyCode)
{
	return (Keyboard::isKeyPressed(keyCode) != m_wasKeyDownLastFrame[keyCode])
		&& !m_wasKeyDownLastFrame[keyCode];
}

bool InputManager::isKeyReleased(const Keyboard::Key keyCode)
{
	return (Keyboard::isKeyPressed(keyCode) != m_wasKeyDownLastFrame[keyCode]) && m_wasKeyDownLastFrame[keyCode];
}


bool InputManager::isButtonDown(const ControllerButtonMapping buttonIdx, const int playerIdx)
{
	return Joystick::isButtonPressed(playerIdx, buttonIdx);
}

bool InputManager::isButtonUp(const ControllerButtonMapping buttonIdx, const int playerIdx)
{
	return !Joystick::isButtonPressed(playerIdx, buttonIdx);
}

bool InputManager::isButtonPressed(const ControllerButtonMapping buttonIdx, const int playerIdx)
{
	return (Joystick::isButtonPressed(playerIdx, buttonIdx) != m_wasButtonDownLastFrame[playerIdx][buttonIdx])
		&& !m_wasButtonDownLastFrame[playerIdx][buttonIdx];
}

bool InputManager::isButtonReleased(const ControllerButtonMapping buttonIdx, const int playerIdx)
{
	return (Joystick::isButtonPressed(playerIdx, buttonIdx) != m_wasButtonDownLastFrame[playerIdx][buttonIdx])
		&& m_wasButtonDownLastFrame[playerIdx][buttonIdx];
}

bool InputManager::isStickPushed(const ControllerStickMapping stickIdx, const int playerIdx)
{
	float leftStickHorizontalValue = Joystick::getAxisPosition(playerIdx, Joystick::Axis::X);
	float leftStickVerticalValue = Joystick::getAxisPosition(playerIdx, Joystick::Axis::Y);
	float rightStickHorizontalValue = Joystick::getAxisPosition(playerIdx, Joystick::Axis::Z);
	float rightStickVerticalValue = Joystick::getAxisPosition(playerIdx, Joystick::Axis::U);

	float threshhold = 20.f;

	switch (stickIdx)
	{
	case LEFT_STICK_DOWN:
		return leftStickVerticalValue >= threshhold;
	case LEFT_STICK_UP:
		return leftStickVerticalValue <= -threshhold;
	case LEFT_STICK_LEFT:
		return leftStickHorizontalValue <= -threshhold;
	case LEFT_STICK_RIGHT:
		return leftStickHorizontalValue >= threshhold;
	case RIGHT_STICK_DOWN:
		return rightStickVerticalValue >= threshhold;
	case RIGHT_STICK_UP:
		return rightStickVerticalValue <= -threshhold;
	case RIGHT_STICK_LEFT:
		return rightStickHorizontalValue <= -threshhold;
	case RIGHT_STICK_RIGHT:
		return rightStickHorizontalValue >= threshhold;
	default:
		break;
	}
}

bool InputManager::isButtonDown(const InputActions action, const int playerIdx)
{
	if (m_buttonBindings[playerIdx].find(action) == m_buttonBindings[playerIdx].end())
		return false;

	ControllerButtonMapping buttonCode = m_buttonBindings[playerIdx][action];
	return isButtonDown(buttonCode, playerIdx);
}

bool InputManager::isButtonUp(const InputActions action, const int playerIdx)
{
	if (m_buttonBindings[playerIdx].find(action) == m_buttonBindings[playerIdx].end())
		return false;

	ControllerButtonMapping buttonCode = m_buttonBindings[playerIdx][action];
	return isButtonUp(buttonCode, playerIdx);
}

bool InputManager::isButtonPressed(const InputActions action, const int playerIdx)
{
	if (m_buttonBindings[playerIdx].find(action) == m_buttonBindings[playerIdx].end())
		return false;

	ControllerButtonMapping buttonCode = m_buttonBindings[playerIdx][action];
	return isButtonPressed(buttonCode, playerIdx);
}

bool InputManager::isButtonReleased(const InputActions action, const int playerIdx)
{
	if (m_buttonBindings[playerIdx].find(action) == m_buttonBindings[playerIdx].end())
		return false;

	ControllerButtonMapping buttonCode = m_buttonBindings[playerIdx][action];
	return isButtonReleased(buttonCode, playerIdx);
}

bool InputManager::isStickPushed(const InputActions action, const int playerIdx)
{
	if (m_stickBindings[playerIdx].find(action) == m_stickBindings[playerIdx].end())
		return false;

	ControllerStickMapping stickCode = m_stickBindings[playerIdx][action];
	return isStickPushed(stickCode, playerIdx);
}

bool InputManager::isActionActive(const InputActions action, const int playerIdx)
{
	return isKeyPressed(action, playerIdx) || isButtonPressed(action, playerIdx) || isStickPushed(action, playerIdx);
}

bool InputManager::isKeyDown(const InputActions action, const int playerIndex)
{
	if (m_keyBindings[playerIndex].find(action) == m_keyBindings[playerIndex].end())
		return false;
	
	Keyboard::Key keyCode = m_keyBindings[playerIndex][action];
	return isKeyDown(keyCode);
}

bool InputManager::isKeyUp(const InputActions action, const int playerIndex)
{
	if (m_keyBindings[playerIndex].find(action) == m_keyBindings[playerIndex].end())
		return false;

	Keyboard::Key keyCode = m_keyBindings[playerIndex][action];
	return isKeyUp(keyCode);
}

bool InputManager::isKeyPressed(const InputActions action, const int playerIndex)

{
	if (m_keyBindings[playerIndex].find(action) == m_keyBindings[playerIndex].end())
		return false;

	Keyboard::Key keyCode = m_keyBindings[playerIndex][action];
	return isKeyPressed(keyCode);
}

bool InputManager::isKeyReleased(const InputActions action, const int playerIndex)
{
	if (m_keyBindings[playerIndex].find(action) == m_keyBindings[playerIndex].end())
		return false;

	Keyboard::Key keyCode = m_keyBindings[playerIndex][action];
	return isKeyReleased(keyCode);
}


bool InputManager::bind(const InputActions action, const Keyboard::Key keyCode, const int playerIndex)
{
	// BUG probably bugy because playerindex can be higher than possible range eg. playerindex = 10 and size = 2 -> exception
	if (playerIndex <= m_keyBindings.size()) 
		m_keyBindings.push_back(std::map<const InputActions, const Keyboard::Key>());

	if (m_keyBindings[playerIndex].find(action) != m_keyBindings[playerIndex].end())
		return false;
	
	m_wasKeyDownLastFrame.insert(std::make_pair(keyCode, false));
	m_keyBindings[playerIndex].insert(std::make_pair(action, keyCode));
	
	return true;
}

bool InputManager::unbind(const InputActions action, const int playerIndex)
{
	bool success = false;
	if (m_keyBindings[playerIndex].find(action) != m_keyBindings[playerIndex].end())
	{	
		m_wasKeyDownLastFrame.erase(m_keyBindings[playerIndex][action]);
		m_keyBindings[playerIndex].erase(action);

		success = true;
	}
	if (m_buttonBindings[playerIndex].find(action) != m_buttonBindings[playerIndex].end())
	{
		m_wasButtonDownLastFrame[playerIndex].erase(m_buttonBindings[playerIndex][action]);
		m_buttonBindings[playerIndex].erase(action);

		success =  true;
	}
	if (m_stickBindings[playerIndex].find(action) != m_stickBindings[playerIndex].end())
	{
		m_stickBindings[playerIndex].erase(action);

		success = true;
	}

	return success;
}

bool InputManager::bind(const InputActions action, const ControllerButtonMapping buttonCode, const int playerIndex)
{
	// BUG probably bugy because playerindex can be higher than possible range eg. playerindex = 10 and size = 2 -> exception
	if (playerIndex <= m_buttonBindings.size()) 
		m_buttonBindings.push_back(std::map<const InputActions, const ControllerButtonMapping>());

	if (playerIndex <= m_wasButtonDownLastFrame.size())
		m_wasButtonDownLastFrame.push_back(std::map<ControllerButtonMapping, bool>());

	if (m_buttonBindings[playerIndex].find(action) != m_buttonBindings[playerIndex].end())
		return false;

	m_wasButtonDownLastFrame[playerIndex].insert(std::make_pair(buttonCode, false));
	m_buttonBindings[playerIndex].insert(std::make_pair(action, buttonCode));

	return true;
}

bool InputManager::bind(const InputActions action, const ControllerStickMapping stickCode, const int playerIndex)
{
	// BUG probably bugy because playerindex can be higher than possible range eg. playerindex = 10 and size = 2 -> exception
	if (playerIndex <= m_stickBindings.size()) 
		m_stickBindings.push_back(std::map<const InputActions, const ControllerStickMapping>());


	if (m_stickBindings[playerIndex].find(action) != m_stickBindings[playerIndex].end())
		return false;

	m_stickBindings[playerIndex].insert(std::make_pair(action, stickCode));

	return true;
}

InputManager& InputManager::getInstance() 
{
	static InputManager m_instance;
	return m_instance;
}

