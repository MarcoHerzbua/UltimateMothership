#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameplayState.h"

using namespace std;
using namespace sf;

#pragma endregion

class GameplaySelectionState : public IGameplayState
{
public:
	GameplaySelectionState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;

};