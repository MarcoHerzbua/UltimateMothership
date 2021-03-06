#pragma region include

#include "stdafx.h"
#include "MenuState.h"

#include "GameStateManager.h"
#include "GameObjectManager.h"

#include "TmxLoader.h"
#pragma endregion

MenuState::MenuState()
{
	m_id = GameStates::MENU_STATE;

	GameStateManager::getInstance().registerState(GameStates::MENU_STATE, this);
}

void MenuState::init()
{
	IGameState::init();

	TmxLoader::loadTmxFile("MenuMap.tmx", sf::Vector2f());
}

void MenuState::exit()
{
	IGameState::exit();
}

void MenuState::update(const float deltaTimeSeconds)
{
	m_gameObjectManager->update(deltaTimeSeconds);

	handleKeyInput();
}


void MenuState::handleKeyInput()
{
	//if (m_inputManager->isKeyPressed(InputActions::B_BUTTON_ACTION, 0))
	//{
	//	RenderWindow * window = m_gameStateManager->getGamePtr()->getWindowPtr();
	//	window->close();
	//}
	
	//if (m_inputManager->isKeyPressed(InputActions::CONFIRM_ACTION, 0))
	//{
	//	m_gameStateManager->setState(GameStates::MAIN_STATE);
	//}
}