#pragma region include

#pragma once
#include "stdafx.h"

#include "GameStates.h"

class InputManager;
class GameStateManager;
class RenderManager;
class GameObjectManager;
class PlayerManager;

using namespace std;
using namespace sf;

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
	PlayerManager* m_playerManager;

	virtual void handleKeyInput() = 0;
};
