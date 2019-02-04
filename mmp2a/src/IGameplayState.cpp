#include "stdafx.h"
#include "IGameplayState.h"

void IGameplayState::init()
{
	m_gameplayStateManager = &GameplayStateManager::getInstance();
}

void IGameplayState::exit()
{
}
