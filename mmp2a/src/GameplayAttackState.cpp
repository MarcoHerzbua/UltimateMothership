#include "stdafx.h"
#include "GameplayAttackState.h"
#include "..\include\GameplayAttackState.h"

GameplayAttackState::GameplayAttackState()
{
	m_id = ATTACK_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplayAttackState::init()
{
	IGameplayState::init();
}

void GameplayAttackState::update(const float deltaTimeSeconds)
{
	auto playerMng = &PlayerManager::getInstance();
	//decrease Movement to 0
	playerMng->getActiveShip()->decreasMovement(playerMng->getActiveShip()->getCurrentMovement());

	playerMng->getActiveShip()->resolveTargets(BASIC_ATTACK_ABILITY);
	m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
	playerMng->activateNextUnit();
}

void GameplayAttackState::exit()
{
}

void GameplayAttackState::handleKeyInput()
{
}
