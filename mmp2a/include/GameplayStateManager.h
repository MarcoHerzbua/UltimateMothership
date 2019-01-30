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

	void init(Game * game);

	void update(const float deltaTimeSeconds);

	void exit();

	void onEvent(IGameEvent * event) override;

	void registerState(GameplayStates name, IGameplayState * state);
	void setState(GameplayStates name);

	// ====================================================

	Game * getGamePtr() { return m_game; };

private:
	GameplayStateManager(void) = default;
	~GameplayStateManager(void) = default;
	GameplayStateManager(const GameplayStateManager& p) = delete;
	GameplayStateManager& operator=(GameplayStateManager const&) = delete;

	void setState(IGameplayState * state);

	// ====================================================

	Game * m_game;

	IGameplayState * m_currentState = nullptr;
	std::map<GameplayStates, IGameplayState *> m_states;

	bool m_firstRegister = true;
};