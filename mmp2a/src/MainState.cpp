#pragma region include

#include "stdafx.h"
#include "MainState.h"

// game classes
#include "Game.h"

// singleton
#include "InputManager.h"
#include "GameStateManager.h"
//#include "PhysicsManager.h"

#include "GameEventClasses.h"
#include "TmxLoader.h"

#pragma endregion

MainState::MainState()
{
	m_id = GameStates::MAIN_STATE;

	GameStateManager::getInstance().registerState(GameStates::MAIN_STATE, this);
}

void MainState::init()
{
	IGameState::init();

	m_playerManager->registerPlayer(0);
	m_playerManager->registerPlayer(1);

	TmxLoader::loadTmxFile("SpaceMapTesting.tmx", Vector2f());
}

void MainState::update(const float deltaTimeSeconds)
{
	m_gameObjectManager->update(deltaTimeSeconds);
	m_playerManager->update(deltaTimeSeconds);
	
	handleKeyInput();
}


void MainState::handleKeyInput()
{
	if (m_inputManager->isActionActive(InputActions::EXIT_ACTION, 0))
	{
		m_gameStateManager->setState(GameStates::MENU_STATE);
	}
	if (m_inputManager->isActionActive(InputActions::SWITCH_STATE_ACTION, 0))
	{
		Eventbus::getInstance().fireEvent(new TogglePopupEvent());
	}

}

