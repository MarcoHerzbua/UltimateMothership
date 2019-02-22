#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameState.h"

using namespace std;
using namespace sf;
#pragma endregion

class ControlsState : public IGameState
{
public:
	ControlsState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;
};