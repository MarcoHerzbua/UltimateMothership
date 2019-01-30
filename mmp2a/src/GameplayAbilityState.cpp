#include "stdafx.h"
#include "GameplayAbilityState.h"

GameplayAbilityState::GameplayAbilityState()
{
	m_id = ABILITY_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);
}

void GameplayAbilityState::init()
{
	IGameplayState::init();
}

void GameplayAbilityState::update(const float deltaTimeSeconds)
{
}

void GameplayAbilityState::exit()
{
}

void GameplayAbilityState::handleKeyInput()
{
}
