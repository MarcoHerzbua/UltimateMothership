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
	//TODO: implement Cursor Conrols here
}
