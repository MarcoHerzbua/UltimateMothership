#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameplayState.h"
#include "IEventListener.h"

class IGameEvent;

using namespace std;
using namespace sf;

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