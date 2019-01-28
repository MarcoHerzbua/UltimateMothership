#pragma region include

#include "stdafx.h"
#include "SteeringComponent.h"

#include "HumanControllerComponent.h"
#include "AIControllerComponent.h"

#include "InputManager.h"
#include "GameObjectManager.h"

#include "ControllerComponent.h"

#include "GameObject.h"

#pragma endregion

SteeringComponent::SteeringComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	m_id = STEERING_COMPONENT;
}

SteeringComponent::SteeringComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = STEERING_COMPONENT;
}

void SteeringComponent::update(const float deltaTimeSeconds)
{ 
	//TODO movement of GameObject -> could be moved to a MovementManager etc (like physicsManager without physics)
	m_gameObject->setPosition(m_currentNode->getPosition()); 

	addTimeSinceLastInput(deltaTimeSeconds);


	//TODO: Just for testing, add functionality somewhere else
	if (InputManager::getInstance().isKeyPressed(SWITCH_HUMAN_AI, m_playerIndex))
	{
		if (m_aiControlled)
		{
			setActiveController(findController(HUMAN_CONTROLLER_COMPONENT));
			m_aiControlled = false;
		}
		else
		{
			setActiveController(findController(AI_CONTROLLER_COMPONENT));
			m_aiControlled = true;
		}
	}

	m_activeController->update(deltaTimeSeconds);
}

void SteeringComponent::exit()
{
	for (auto c : m_controller)
	{
		c->exit();
		delete c;
	}
	m_controller.clear();
}

void SteeringComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	int startRow = 0;
	int startCol = 0;

	m_playerIndex = 0;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "PlayerIndex")
			m_playerIndex = stoi(property->value);
		if (name == "StartRow")
			startRow = stoi(property->value);
		if (name == "StartCol")
			startCol = stoi(property->value);
	}

	auto human = new HumanControllerComponent(m_gameObject, this, *m_mapObject);
	human->initTmxData();
	registerController(human);

	auto ai = new AIControllerComponent(m_gameObject, this, *m_mapObject);
	ai->initTmxData();
	registerController(ai);

	setActiveController(human);
	m_aiControlled = false;


	auto nodeGraphRenderComp = static_cast<NodeGraphRenderComponent*>(GameObjectManager::getInstance().findGameObjects(TILEMAP_OBJECT)[0]->findComponents(NODE_GRAPH_RENDER_COMPONENT)[0]);
	m_currentNode = nodeGraphRenderComp->getGraph().getNodeOnPos(startRow, startCol);
	
	setCurrentNode(m_currentNode);

	m_mapObject = nullptr;
}


void SteeringComponent::registerController(ControllerComponent* c)
{
	m_controller.push_back(c);

	if (!m_activeController)
		setActiveController(c);
}
void SteeringComponent::removeController(ControllerComponents cId)
{
	if (m_activeController->getId() == cId)
	{
		err() << "Unable to remove an active Controller from SteeringComponent. Please swap active Controllers before deleting Controller!";
		return;
	}

	auto cIti = findControllerIterator(cId);

	if (cIti != m_controller.end())
	{
		m_controller.erase(cIti);
		(*cIti)->exit();
		delete (*cIti);
	}
}
ControllerComponent* SteeringComponent::findController(ControllerComponents cId)
{
	auto cIti = findControllerIterator(cId);

	if (cIti != m_controller.end()) return *cIti;

	return nullptr;
}
vector<ControllerComponent*>::iterator SteeringComponent::findControllerIterator(const ControllerComponents cId)
{
	for (auto cIti = m_controller.begin(); cIti != m_controller.end(); cIti++)
	{
		if ((*cIti)->getId() == cId) return cIti;
	}

	return m_controller.end();
}


void SteeringComponent::setActiveController(ControllerComponents cId)
{
	m_activeController = findController(cId);
	m_activeController->activate();
}
void SteeringComponent::setActiveController(ControllerComponent* c)
{
	m_activeController = c;
	m_activeController->activate();
}
