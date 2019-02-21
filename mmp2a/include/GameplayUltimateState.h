#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameplayState.h"

#include "GameObjects.h"

using namespace std;
using namespace sf;

#pragma endregion

class GameplayUltimateState : public IGameplayState
{
public:
	GameplayUltimateState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;

	vector<GameObjects> getPossibleEnemyShipIDs(GameObjects go);

};