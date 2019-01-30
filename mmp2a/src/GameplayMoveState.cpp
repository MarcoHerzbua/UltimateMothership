#include "stdafx.h"
#include "GameplayMoveState.h"

GameplayMoveState::GameplayMoveState()
{
	m_id = MOVE_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplayMoveState::init()
{
	IGameplayState::init();
}

void GameplayMoveState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayMoveState::exit()
{
}

void GameplayMoveState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		//TODO: Move Unit to the chosen Node or show pop up if not possible
		if (/*Node is out of range*/ true)
		{
			Eventbus::getInstance().fireEvent(
				new GameplayStateChangeEvent(this, this));
			Eventbus::getInstance().fireEvent(new UpdatePopupEvent(
				"The chosen Unit is unable to move to this location! Try Again!"));
		}
		else
		{
			//TODO: Move Unit to Node
			m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
			playerMng->activateNextUnit();
			//TODO: Lock unit so it can't be moved again
		}
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
	}
}
