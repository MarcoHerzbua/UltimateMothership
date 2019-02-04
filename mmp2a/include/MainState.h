#pragma region include

#pragma once
#include "stdafx.h"
#include "GameplayStateManager.h"

// interface
#include "IGameState.h"

// forward declaration
class GameStateManager;

#pragma endregion

class MainState : public virtual IGameState
{
public:
	MainState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;

	GameplayStateManager * m_gameplayStateManager;
};