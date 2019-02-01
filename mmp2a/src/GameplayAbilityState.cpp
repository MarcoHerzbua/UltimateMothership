#include "stdafx.h"
#include "GameplayAbilityState.h"
#include "CursorComponent.h"
#include "SteeringComponent.h"
#include "GameObjects.h"
#include "IAbilityComponent.h"
#include "Stats.h"
#include "MotherShipComponent.h"

GameplayAbilityState::GameplayAbilityState()
{
	m_id = ABILITY_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);
}

void GameplayAbilityState::init()
{
	IGameplayState::init();
}

void GameplayAbilityState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayAbilityState::exit()
{
}

void GameplayAbilityState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();

	playerMng->getCursor()->setPossibleRange(0);

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		if (playerMng->getActiveShip()->getCurrentMovement() == 0)
		{
			auto selectState = m_gameplayStateManager->getState(SELECTION_GAMEPLAY_STATE);
			Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(selectState, selectState));
			Eventbus::getInstance().fireEvent(
				new	UpdatePopupEvent("Unit cannot attack anymore this round! Let me switch to the next Unit for you :*"));
			playerMng->activateNextUnit();
			return;
		}
		else
			m_gameplayStateManager->setState(ATTACK_GAMEPLAY_STATE);
	}
	if (InputManager::getInstance().isActionActive(X_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		if (playerMng->getActiveShip()->getCurrentMovement() == 0)
		{
			auto selectState = m_gameplayStateManager->getState(SELECTION_GAMEPLAY_STATE);
			Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(selectState, selectState));
			Eventbus::getInstance().fireEvent(
				new	UpdatePopupEvent("Unit cannot attack anymore this round! Let me switch to the next Unit for you :*"));
			playerMng->activateNextUnit();
			return;
		}
		else
			m_gameplayStateManager->setState(ULTIMATE_GAMEPLAY_STATE);

	}

	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
	}

}


