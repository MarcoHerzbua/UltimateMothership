#pragma region include

#include "stdafx.h"
#include "MenuState.h"

// game classes
#include "Game.h"
#include "GameObject.h"

// components
#include "SpriteRenderComponent.h"
#include "GUIRenderComponent.h"

// singleton
#include "InputManager.h"
#include "GameStateManager.h"
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

void MenuState::update(const float deltaTimeSeconds)
{
	m_gameObjectManager->update(deltaTimeSeconds);

	handleKeyInput();
}

void MenuState::onEvent(IGameEvent * event)
{
	if (event->getID() == START_GAME_EVENT)
		m_gameStateManager->setState(GameStates::MAIN_STATE);
	if (event->getID() == EXIT_GAME_EVENT)
	{
		RenderWindow * window = GameStateManager::getInstance().getGamePtr()->getWindowPtr();
		window->close();
	}
}


void MenuState::handleKeyInput()
{
	//if (m_inputManager->isKeyPressed(InputActions::EXIT_ACTION, 0))
	//{
	//	RenderWindow * window = m_gameStateManager->getGamePtr()->getWindowPtr();
	//	window->close();
	//}
	
	//if (m_inputManager->isKeyPressed(InputActions::SWITCH_STATE_ACTION, 0))
	//{
	//	m_gameStateManager->setState(GameStates::MAIN_STATE);
	//}
}