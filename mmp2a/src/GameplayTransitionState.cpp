#include "stdafx.h"
#include "GameplayTransitionState.h"

#include "GameplayStateManager.h"
#include "GameEventClasses.h"
#include "PlayerManager.h"
#include "InputManager.h"
#include "Eventbus.h"

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
		Eventbus::getInstance().fireEvent(new TogglePopupEvent(true));
	}
}

void GameplayTransitionState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();
	if (InputManager::getInstance().isActionActive(InputActions::A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		Eventbus::getInstance().fireEvent(new TogglePopupEvent(false));
		m_gameplayStateManager->setState(m_nextState->getID());
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		Eventbus::getInstance().fireEvent(new TogglePopupEvent(false));
		m_gameplayStateManager->setState(m_previousState->getID());
	}
}
