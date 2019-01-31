#include "stdafx.h"
#include "CursorComponent.h"

#include "GameObject.h"
#include "SteeringComponent.h"
#include "PlayerManager.h"
#include "InputManager.h"
#include "AIControllerComponent.h"
#include "GameObjectManager.h"

#include "ShipComponent.h"
#include "SpriteSwitcherComponent.h"

CursorComponent::CursorComponent(GameObject* gameObject)
	: IGameComponent(gameObject)
{
#include "Stats.h"
	m_id = CURSOR_COMPONENT;
}

CursorComponent::CursorComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = CURSOR_COMPONENT;
}

void CursorComponent::update(const float deltaTimeSeconds)
{
}

void CursorComponent::updateCursor(const float deltaTimeSeconds)
{
	m_steering->updateUnit(deltaTimeSeconds); // move cursor

	auto graph = &static_cast<NodeGraphRenderComponent*>(GameObjectManager::getInstance().findGameObjects(TILEMAP_OBJECT)[0]->findComponents(NODE_GRAPH_RENDER_COMPONENT)[0])->getGraph();
	
	m_distanceToActive = graph->calcDistance(*(PlayerManager::getInstance().getActiveUnit()->getCurrentNode()), *(m_steering->getCurrentNode()));

	bool moveInRange = PlayerManager::getInstance().getActiveShip()->getCurrentMovement() >= m_distanceToActive;

	auto switcher = static_cast<SpriteSwitcherComponent*>(m_gameObject->findComponents(SPRITE_SWITCHER_COMPONENT)[0]);

	if (!moveInRange)
		switcher->activateSet(1);
	else
		switcher->activateSet(0);

	if (InputManager::getInstance().isKeyPressed(MOVE_ABILITY_ACTION, m_steering->getPlayerIndex()))
	{
		if (moveInRange)
		{
			PlayerManager::getInstance().getActiveUnit()->moveToTargetNode(m_steering->getCurrentNode());
			PlayerManager::getInstance().getActiveShip()->decreasMovement(m_distanceToActive);
		}
	}
}

void CursorComponent::exit()
{
}

void CursorComponent::initTmxData()
{
	auto s = static_cast<SteeringComponent*>(m_gameObject->findComponents(STEERING_COMPONENT)[0]);
	m_steering = s;

	m_steering->setActiveController(HUMAN_CONTROLLER_COMPONENT);

	PlayerManager::getInstance().registerCursor(this);



}
