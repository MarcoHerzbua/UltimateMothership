#pragma region include

#include "stdafx.h"
#include "IGameState.h"

#include "InputManager.h"
#include "GameStateManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "PlayerManager.h"

#pragma endregion

void IGameState::init()
{
	m_gameStateManager = &GameStateManager::getInstance();
	m_inputManager = &InputManager::getInstance();

	m_renderManager = &RenderManager::getInstance();
	m_gameObjectManager = &GameObjectManager::getInstance();

	m_playerManager = &PlayerManager::getInstance();
}

void IGameState::exit()
{
	if (m_renderManager) m_renderManager->clearComponents();
	if (m_gameObjectManager) m_gameObjectManager->clearGameObjects();
	if (m_playerManager) m_playerManager->clearComponents();
}