#pragma region include

#pragma once
#include "stdafx.h"

#include "GameplayStates.h"

class GameplayStateManager;

#pragma endregion

class IGameplayState
{
public:
	virtual ~IGameplayState() = default;

	virtual void init();

	virtual void update(const float deltaTimeSeconds) = 0;

	virtual void exit();

	virtual GameplayStates getID() { return m_id; };
protected:
	GameplayStates m_id;

	GameplayStateManager * m_gameplayStateManager;

	virtual void handleKeyInput() = 0; // TODO remove handlyKeyInput
};
