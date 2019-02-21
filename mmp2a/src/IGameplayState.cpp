#include "stdafx.h"
#include "IGameplayState.h"

#include "GameplayStateManager.h"

void IGameplayState::init()
{
	m_gameplayStateManager = &GameplayStateManager::getInstance();
}

void IGameplayState::exit()
{
}
