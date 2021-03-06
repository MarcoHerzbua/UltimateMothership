#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameplayState.h"
#include "IEventListener.h"

class IGameEvent;

using namespace std;
using namespace sf;

#pragma endregion

class GameplayTransitionState 
	: public IGameplayState
	, public IEventListener
{
public:
	GameplayTransitionState();

	void init() override;

	void update(const float deltaTimeSeconds) override;

	void exit() override;

	void onEvent(IGameEvent * event) override;

	void setNextState(IGameplayState * next) { m_nextState = next; };
	void setPreviousState(IGameplayState * prev) { m_previousState = prev; };

private:
	void handleKeyInput() override;

	IGameplayState * m_previousState;
	IGameplayState * m_nextState;

};