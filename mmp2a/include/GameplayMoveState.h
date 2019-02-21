#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameplayState.h"

using namespace std;
using namespace sf;

#pragma endregion

class GameplayMoveState : public IGameplayState
{
public:
	GameplayMoveState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;

};