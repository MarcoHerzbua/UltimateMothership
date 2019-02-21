#include "stdafx.h"
#include "GameplayGameOverState.h"

#include "GameStateManager.h"
#include "GameplayStateManager.h"
#include "PlayerManager.h"
#include "InputManager.h"

GameplayGameOverState::GameplayGameOverState()
{
	m_id = GAME_OVER_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplayGameOverState::init()
{
	IGameplayState::init();
}

void GameplayGameOverState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayGameOverState::exit()
{
}

void GameplayGameOverState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, 0)
		|| InputManager::getInstance().isActionActive(A_BUTTON_ACTION, 1))
	{
		GameStateManager::getInstance().setState(MENU_STATE);
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, 0)
		|| InputManager::getInstance().isActionActive(B_BUTTON_ACTION, 1))
	{
		GameStateManager::getInstance().setState(MENU_STATE);
	}
}
