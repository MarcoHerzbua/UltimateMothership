#pragma region include

#pragma once
#include "stdafx.h"
#include "IGameplayState.h"

// enums
#include "GameplayStates.h"

// singleton
#include "GameplayStateManager.h"

#pragma endregion

class GameplayAbilityState : public IGameplayState
{
public:
	GameplayAbilityState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;
	vector<GameObjects> getPossibleEnemyShipIDs(GameObjects go);
};