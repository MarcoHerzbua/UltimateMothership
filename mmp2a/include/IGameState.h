#pragma region include

#pragma once
#include "stdafx.h"

// game classes
#include "GameObject.h"

// enums
#include "GameStates.h"

// singleton
#include "InputManager.h"
#include "GameStateManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "PlayerManager.h"

#include "HelperMethods.h"
#pragma endregion

class IGameState
{
public:
	virtual ~IGameState() = default;

	virtual void init();

	virtual void update(const float deltaTimeSeconds) = 0;

	virtual void exit();

protected:
	GameStates m_id;

	GameStateManager * m_gameStateManager;
	InputManager * m_inputManager;

	RenderManager * m_renderManager;
	GameObjectManager * m_gameObjectManager;
	PhysicsManager * m_physicsManager;

	virtual void handleKeyInput() = 0;
};
