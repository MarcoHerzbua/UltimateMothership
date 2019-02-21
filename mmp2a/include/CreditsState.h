#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameState.h"

using namespace std;
using namespace sf;
#pragma endregion

class CreditsState : public IGameState
{
public:
	CreditsState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

private:
	void handleKeyInput() override;
};