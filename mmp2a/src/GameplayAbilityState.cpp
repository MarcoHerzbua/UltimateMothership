#include "stdafx.h"
#include "GameplayAbilityState.h"
#include "CursorComponent.h"
#include "SteeringComponent.h"

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

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		auto cursorNode = playerMng->getCursor()->getCurrentNode();
		auto shipNode = playerMng->getActiveUnit()->g
		Eventbus::getInstance().fireEvent(
			new GameplayStateChangeEvent(this, m_gameplayStateManager->getState(ATTACK_GAMEPLAY_STATE)));
		Eventbus::getInstance().fireEvent(
			new UpdatePopupEvent("You are about to attack an enemy!! Continue?"));
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
	}

}
