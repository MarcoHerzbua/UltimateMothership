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
}

void GameplayAttackState::exit()
{
}

void GameplayAttackState::handleKeyInput()
{
}
