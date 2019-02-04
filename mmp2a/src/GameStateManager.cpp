#pragma region include

#include "stdafx.h"
#include "GameStateManager.h"

// game classes
#include "Game.h"

// interface
#include "IGameState.h"

#pragma endregion


void GameStateManager::init(Game * game)
{
	m_game = game;
}

void GameStateManager::registerState(GameStates name, IGameState * state)
{
	m_states.insert(std::make_pair(name, state));

	if (m_firstRegister)
	{
		setState(state);
		m_firstRegister = false;
	}
}

void GameStateManager::setState(GameStates name)
{
	setState(m_states[name]);
}

void GameStateManager::setState(IGameState * state)
{
	if (m_currentState != state)
	{
		if (m_currentState)
			m_currentState->exit();

		m_currentState = state;
		m_currentState->init();
	}
}


void GameStateManager::update(const float deltaTimeSeconds)
{
	m_currentState->update(deltaTimeSeconds);
}

void GameStateManager::exit()
{
	m_currentState = nullptr;

	for (auto& keyValuePair : m_states)
	{
		auto state = keyValuePair.second;
		state->exit();
		delete state; 
	}

	m_states.clear();
}

void GameStateManager::onEvent(IGameEvent * event)
{
	auto id = event->getID();

	switch (id)
	{
	case START_GAME_EVENT:
		setState(GameStates::MAIN_STATE);
		break;
	case EXIT_GAME_EVENT:
	{
		RenderWindow * window = getGamePtr()->getWindowPtr();
		window->close();
	}
		break;
	case SHOW_CREDITS_EVENT:
		setState(CREDITS_STATE);
		break;
	case BACK_TO_MENU_EVENT:
		setState(MENU_STATE);
		break;
	default:
		break;
	}
}

Game * GameStateManager::getGamePtr()
{
	return m_game;
}

GameStateManager& GameStateManager::getInstance() {
	static GameStateManager m_instance;
	return m_instance;
}



