#include "stdafx.h"
#include "GameplayStateManager.h"
#include "IGameplayState.h"

GameplayStateManager & GameplayStateManager::getInstance()
{
	static GameplayStateManager m_instance;
	return m_instance;
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
		//auto ev = dynamic_cast<GameplayStateChangeEvent*>(event);
		setState(TRANSITION_GAMEPLAY_STATE);
	}
	if (event->getID() == TOGGLE_GAME_OVER_EVENT)
	{
		setState(GAME_OVER_GAMEPLAY_STATE);
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
	auto eventBus = &Eventbus::getInstance();

	switch (name)
	{
	case(TRANSITION_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Popup", "Confirm", "Decline", "", "" }));
		break;
	case(SELECTION_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Selection", "Move", "End Turn", "Use Abilities", "Recruit" }));
		break;	
	case(ABILITY_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Abilities", "Attack", "Back to Unitselect", "Ultimate (12 res)", "" }));
		break;
	case(MOVE_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Move", "Confirm Move", "Back to Unitselect", "", "" }));
		break;
	case(END_TURN_GAMEPLAY_STATE):
		eventBus->fireEvent(new GameplayEndTurnEvent());
		break;
	case(GAME_OVER_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Game Over", "Confirm", "Decline", "", "" }));
		break;
	case(ULTIMATE_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Ultimate", "Use", "Back to Abilities", "", "" }));
		break;
	case(ATTACK_GAMEPLAY_STATE):
		eventBus->fireEvent(new UpdateButtonMapEvent({ "Attack", "Confirm Attack", "Back to Abilities", "", "" }));
		break;
	default:
		break;
	}
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

