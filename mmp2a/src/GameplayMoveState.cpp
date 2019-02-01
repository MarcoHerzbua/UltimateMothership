#include "stdafx.h"
#include "GameplayMoveState.h"
#include "NodeGraphRenderComponent.h"
#include "GameObjectManager.h"
#include "SteeringComponent.h"
#include "CursorComponent.h"
#include "ShipComponent.h"

GameplayMoveState::GameplayMoveState()
{
	m_id = MOVE_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplayMoveState::init()
{
	IGameplayState::init();
}

void GameplayMoveState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayMoveState::exit()
{
}

void GameplayMoveState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();

	if (PlayerManager::getInstance().getActiveUnit()->isMoving())
		return;

	playerMng->getCursor()->setPossibleRange(playerMng->getActiveShip()->getCurrentMovement());

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		if (playerMng->getActiveShip()->getCurrentMovement() == 0)
		{
			auto selectState = m_gameplayStateManager->getState(SELECTION_GAMEPLAY_STATE);
			Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(selectState, selectState));
			Eventbus::getInstance().fireEvent(
				new	UpdatePopupEvent("Unit cannot move any further this round! Let me switch to the next Unit for you :*"));
			playerMng->activateNextUnit();
			return;
		}

		auto cursorNode = playerMng->getCursor()->getCurrentNode();
		auto distanceToActive = playerMng->getCursor()->getDistanceToActive();
		
		if (playerMng->getActiveShip()->getCurrentMovement() >= distanceToActive
			&& !cursorNode->isNodeOccupied())
		{
			playerMng->getActiveUnit()->moveToTargetNode(cursorNode);
			playerMng->getActiveShip()->decreasMovement(distanceToActive);
			Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(playerMng->getActiveShip()));
		}
		else
		{
			Eventbus::getInstance().fireEvent(
				new GameplayStateChangeEvent(this, this));
			Eventbus::getInstance().fireEvent(new UpdatePopupEvent(
				"The chosen Unit is unable to move to this location! Try Again!"));
		}
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
	}
}
