#include "stdafx.h"
#include "GameplaySelectionState.h"

GameplaySelectionState::GameplaySelectionState()
{
	m_id = SELECTION_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplaySelectionState::init()
{
	IGameplayState::init();

}

void GameplaySelectionState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplaySelectionState::exit()
{
}

void GameplaySelectionState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();
	if (InputManager::getInstance().isActionActive(NEXT_UNIT_ACTION, playerMng->getActivePlayer()))
	{
		playerMng->activateNextUnit();
	}
	if (InputManager::getInstance().isActionActive(PREV_UNIT_ACTION, playerMng->getActivePlayer()))
	{
		playerMng->activatePrevUnit();
	}
	//if (InputManager::getInstance().isKeyPressed(NEXT_PLAYER_ACTION, playerMng->getActivePlayer()))
	//{
	//	playerMng->activateNextPlayer();
	//}

	if (InputManager::getInstance().isActionActive(X_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(ABILITY_GAMEPLAY_STATE);
		//Eventbus::getInstance().fireEvent(
		//	new GameplayStateChangeEvent(this, m_gameplayStateManager->getInstance().getState(ABILITY_GAMEPLAY_STATE)));
	}
	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(MOVE_GAMEPLAY_STATE);
		//Eventbus::getInstance().fireEvent(
		//	new GameplayStateChangeEvent(this, m_gameplayStateManager->getInstance().getState(MOVE_GAMEPLAY_STATE)));
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		Eventbus::getInstance().fireEvent(
			new GameplayStateChangeEvent(this, m_gameplayStateManager->getInstance().getState(END_TURN_GAMEPLAY_STATE)));
		Eventbus::getInstance().fireEvent(
			new UpdatePopupEvent("You are about to end your turn!! Choose wisely!"));
	}

}
