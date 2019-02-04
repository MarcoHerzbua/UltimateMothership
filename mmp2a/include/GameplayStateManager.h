#pragma region include

#pragma once
#include "stdafx.h"
#include "IEventListener.h"
// enums
#include "GameplayStates.h"

// forward declaration
class Game;
class IGameplayState;

#pragma endregion

class GameplayStateManager 
	: IEventListener
{
public:
	static GameplayStateManager& getInstance();

	void update(const float deltaTimeSeconds);

	void exit();

	void onEvent(IGameEvent * event) override;

	void registerState(GameplayStates name, IGameplayState * state);
	void setState(GameplayStates name);

	// ====================================================

	IGameplayState * getState(GameplayStates state) { return m_states[state]; };
private:
	GameplayStateManager(void) = default;
	~GameplayStateManager(void) = default;
	GameplayStateManager(const GameplayStateManager& p) = delete;
	GameplayStateManager& operator=(GameplayStateManager const&) = delete;

	void setState(IGameplayState * state);
	// ====================================================

	IGameplayState * m_currentState = nullptr;
	std::map<GameplayStates, IGameplayState *> m_states;

	bool m_firstRegister = true;
};