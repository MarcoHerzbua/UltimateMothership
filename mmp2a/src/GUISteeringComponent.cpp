#include "stdafx.h"
#include "GUISteeringComponent.h"
#include "GameObject.h"
#include "GUIControllerComponent.h"

GUISteeringComponent::GUISteeringComponent(GameObject * gameObject)
	:SteeringComponent(gameObject)
{
	m_id = GUI_STEERING_COMPONENT;
}

GUISteeringComponent::GUISteeringComponent(GameObject * gameObject, NLTmxMapObject& mapObject)
	: SteeringComponent(gameObject, mapObject)
{
	m_id = GUI_STEERING_COMPONENT;
}

void GUISteeringComponent::update(const float deltaTimeSeconds)
{
	addTimeSinceLastInput(deltaTimeSeconds);

	m_activeController->update(deltaTimeSeconds);
}

void GUISteeringComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "PlayerIndex")
			m_playerIndex = stoi(property->value);
	}

	auto controller = new GUIControllerComponent(m_gameObject, this, *m_mapObject);
	controller->initTmxData();
	registerController(controller);
	setActiveController(controller);
	m_aiControlled = false;

	setCurrentNode(nullptr);
	m_mapObject = nullptr;


}
