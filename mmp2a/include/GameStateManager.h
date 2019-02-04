#pragma region include

#pragma once
#include "stdafx.h"
#include "IEventListener.h"
// enums
#include "GameStates.h"

// forward declaration
class Game;
class IGameState;

#pragma endregion

class GameStateManager : IEventListener
{
public:
	static GameStateManager& getInstance();

	void init(Game * game);

	void update(const float deltaTimeSeconds);

	void exit();

	void onEvent(IGameEvent * event) override;

	void registerState(GameStates name, IGameState * state);
	void setState(GameStates name);

	// ====================================================

	Game * getGamePtr();

private:
	GameStateManager(void) = default;
	~GameStateManager(void) = default;
	GameStateManager(const GameStateManager& p) = delete;
	GameStateManager& operator=(GameStateManager const&) = delete;
	
	void setState(IGameState * state);

	// ====================================================

	Game * m_game;

	IGameState * m_currentState = nullptr;
	std::map<GameStates, IGameState *> m_states;

	bool m_firstRegister = true;
};