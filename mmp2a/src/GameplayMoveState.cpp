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
}

void GameplayMoveState::exit()
{
}

void GameplayMoveState::handleKeyInput()
{
}
