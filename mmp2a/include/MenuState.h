#pragma region include

#pragma once
#include "stdafx.h"

// interface
#include "IGameState.h"
#include "IEventListener.h"
#include "GameEventClasses.h"

// forward declaration
class GameStateManager;

using namespace std;
using namespace sf;
#pragma endregion

class MenuState 
	: public IGameState
	, public IEventListener
{
public:
	MenuState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void onEvent(IGameEvent * event) override;
private:
	void handleKeyInput() override;
};