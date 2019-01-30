#include "stdafx.h"
#include "GameplayStateManager.h"
#include "IGameplayState.h"

GameplayStateManager & GameplayStateManager::getInstance()
{
	static GameplayStateManager m_instance;
	return m_instance;
}

void GameplayStateManager::init(Game * game)
{
	m_game = game;
}

void GameplayStateManager::update(const float deltaTimeSeconds)
{
	m_currentState->update(deltaTimeSeconds);
}

void GameplayStateManager::exit()
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

void GameplayStateManager::onEvent(IGameEvent * event)
{
	if (event->getID() == GAMEPLAYSTATE_CHANGE_EVENT)
	{
		auto ev = dynamic_cast<GameplayStateChangeEvent*>(event);
		setState(TRANSITION_GAMEPLAY_STATE);
	}
}

void GameplayStateManager::registerState(GameplayStates name, IGameplayState * state)
{
	m_states.insert(std::make_pair(name, state));

	if (m_firstRegister)
	{
		setState(state);
		m_firstRegister = false;
	}

}

void GameplayStateManager::setState(GameplayStates name)
{
	setState(m_states[name]);
}

void GameplayStateManager::setState(IGameplayState * state)
{
	if (m_currentState != state)
	{
		if (m_currentState)
			m_currentState->exit();

		m_currentState = state;
		m_currentState->init();
	}

}

