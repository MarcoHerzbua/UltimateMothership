#pragma region include

#pragma once
#include "stdafx.h"
#include "IGameplayState.h"

// enums
#include "GameplayStates.h"

// singleton
#include "GameplayStateManager.h"

#pragma endregion

class GameplayEndTurnState 
	: public IGameplayState
	, public IEventListener
{
public:
	GameplayEndTurnState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

	void onEvent(IGameEvent * event) override;
private:
	void handleKeyInput() override;

};