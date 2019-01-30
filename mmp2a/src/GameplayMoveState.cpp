#include "stdafx.h"
#include "GameplayMoveState.h"
#include "NodeGraphRenderComponent.h"
#include "GameObjectManager.h"
#include "SteeringComponent.h"
#include "CursorComponent.h"

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

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		auto graph = &static_cast<NodeGraphRenderComponent*>(GameObjectManager::getInstance().findGameObjects(TILEMAP_OBJECT)[0]->findComponents(NODE_GRAPH_RENDER_COMPONENT)[0])->getGraph();
		auto unitNode = playerMng->getActiveUnit()->getCurrentNode();
		auto cursorNode = playerMng->getCursor()->getSteeringComponent()->getCurrentNode();

		auto distanceToActive = graph->calcDistance(*(unitNode), *(cursorNode));
		
		if (PlayerManager::getInstance().getActiveShip()->getCurrentMovement() >= distanceToActive)
		{
			PlayerManager::getInstance().getActiveUnit()->moveToTargetNode(cursorNode);
			PlayerManager::getInstance().getActiveShip()->decreasMovement(distanceToActive);
			m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
			playerMng->activateNextUnit();
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
