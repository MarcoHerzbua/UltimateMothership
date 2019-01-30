#pragma region include

#pragma once
#include "stdafx.h"

// enums
#include "GameplayStates.h"

// singleton
#include "GameplayStateManager.h"
#include "InputManager.h"
#include "GameEventClasses.h"

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

	virtual void handleKeyInput() = 0;
};
