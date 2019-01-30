#include "stdafx.h"
#include "GameplayEndTurnState.h"

GameplayEndTurnState::GameplayEndTurnState()
{
	m_id = END_TURN_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);
}

void GameplayEndTurnState::init()
{
	IGameplayState::init();
}

void GameplayEndTurnState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayEndTurnState::exit()
{
}

void GameplayEndTurnState::onEvent(IGameEvent * event)
{
	if (event->getID() == GAMEPLAYSTATE_END_TURN_EVENT)
	{
		PlayerManager::getInstance().activateNextPlayer();

		//string playerText = "Player " + PlayerManager::getInstance().getActivePlayer();
		Eventbus::getInstance().fireEvent(
			new UpdatePopupEvent("Next Player is now in Control!!"));

		auto selectEvent = m_gameplayStateManager->getState(SELECTION_GAMEPLAY_STATE);
		Eventbus::getInstance().fireEvent(
			new GameplayStateChangeEvent(selectEvent, selectEvent));
	}
}

void GameplayEndTurnState::handleKeyInput()
{
	
}
