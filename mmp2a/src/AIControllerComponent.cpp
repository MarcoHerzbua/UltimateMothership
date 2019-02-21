#pragma region include

#include "stdafx.h"
#include "AIControllerComponent.h"

#include "GameObject.h"
#include "SteeringComponent.h"

#include "InputManager.h"
#include "GameObjectManager.h"

#include "ControllerComponents.h"

#include "AiInputComponent.h"

#include "Node.h"
#include "Graph.h"
#include "NodeGraphRenderComponent.h"

#pragma endregion

AIControllerComponent::AIControllerComponent(GameObject * gameObject, SteeringComponent* steeringComponent)
	: ControllerComponent(gameObject, steeringComponent)
{
	m_id = AI_CONTROLLER_COMPONENT;
}
AIControllerComponent::AIControllerComponent(GameObject * gameObject, SteeringComponent* steeringComponent, NLTmxMapObject & mapObject)
	: ControllerComponent(gameObject, steeringComponent, mapObject)
{
	m_id = AI_CONTROLLER_COMPONENT;
}

void AIControllerComponent::init(Graph* graph)
{
	m_graph = graph;
}

void AIControllerComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	auto comp = new AiInputComponent(m_gameObject, this);
	comp->init();
	registerInput(comp);

	auto tilemapObj = GameObjectManager::getInstance().findGameObjects(TILEMAP_OBJECT)[0];
	auto nodeGraph = static_cast<NodeGraphRenderComponent*>(tilemapObj->findComponents(NODE_GRAPH_RENDER_COMPONENT)[0]);

	init(&(nodeGraph->getGraph()));

	m_mapObject = nullptr;
}

void AIControllerComponent::activate()
{
	cout << "playerIndex: " << m_steeringComponent->getPlayerIndex() << " -- AI active" << endl;
}

void AIControllerComponent::moveToTargetNode(Node* n)
{
	m_aiActionStack = m_graph->getPath(*(m_steeringComponent->getCurrentNode()), *n);
}

InputActions AIControllerComponent::getNextActionFromStack()
{
	if (m_aiActionStack.size() != 0)
	{
		auto action = m_aiActionStack.top();
		m_aiActionStack.pop();
		return action;
	}

	return NULL_ACTION;
}
