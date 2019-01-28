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
	return (Keyboard::isKeyPressed(keyCode) != m_wasKeyDownLastFrame[keyCode]) && !m_wasKeyDownLastFrame[keyCode];
}

bool InputManager::isKeyReleased(const Keyboard::Key keyCode)
{
	return (Keyboard::isKeyPressed(keyCode) != m_wasKeyDownLastFrame[keyCode]) && m_wasKeyDownLastFrame[keyCode];
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
	if (playerIndex <= m_keyBindings.size()) // TODO probably bugy because playerindex can be higher than possible range eg. playerindex = 10 and size = 2 -> exception
		m_keyBindings.push_back(std::map<const InputActions, const Keyboard::Key>());

	if (m_keyBindings[playerIndex].find(action) != m_keyBindings[playerIndex].end())
		return false;
	
	m_wasKeyDownLastFrame.insert(std::make_pair(keyCode, false));
	m_keyBindings[playerIndex].insert(std::make_pair(action, keyCode));
	
	return true;
}

bool InputManager::unbind(const InputActions action, const int playerIndex)
{
	if (m_keyBindings[playerIndex].find(action) == m_keyBindings[playerIndex].end())
		return false;

	m_wasKeyDownLastFrame.erase(m_keyBindings[playerIndex][action]);
	m_keyBindings[playerIndex].erase(action);

	return true;
}

InputManager& InputManager::getInstance() 
{
	static InputManager m_instance;
	return m_instance;
}

