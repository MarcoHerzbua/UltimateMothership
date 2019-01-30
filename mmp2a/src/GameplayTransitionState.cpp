#include "stdafx.h"
#include "GameplayTransitionState.h"

GameplayTransitionState::GameplayTransitionState()
{
	m_id = TRANSITION_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplayTransitionState::init()
{
	IGameplayState::init();

}

void GameplayTransitionState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayTransitionState::exit()
{
}

void GameplayTransitionState::onEvent(IGameEvent * event)
{
	if (event->getID() == GAMEPLAYSTATE_CHANGE_EVENT)
	{
		auto ev = dynamic_cast<GameplayStateChangeEvent*>(event);
		setNextState(ev->m_next);
		setPreviousState(ev->m_prev);
	}
}

void GameplayTransitionState::handleKeyInput()
{
	if (InputManager::getInstance().isActionActive(InputActions::SWITCH_STATE_ACTION, 0))
	{
		Eventbus::getInstance().fireEvent(new TogglePopupEvent());
		m_gameplayStateManager->setState(m_nextState->getID());
	}
	if (InputManager::getInstance().isActionActive(EXIT_ACTION, 0))
	{
		Eventbus::getInstance().fireEvent(new TogglePopupEvent());
		m_gameplayStateManager->setState(m_previousState->getID());
	}
}
