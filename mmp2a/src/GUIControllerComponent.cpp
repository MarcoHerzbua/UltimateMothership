#include "stdafx.h"
#include "GUIControllerComponent.h"

GUIControllerComponent::GUIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent)
	: ControllerComponent(gameObject, steeringComponent)
{
	m_id = GUI_CONTROLLER_COMPONENT;
}

GUIControllerComponent::GUIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject)
	: ControllerComponent(gameObject, steeringComponent, mapObject)
{
	m_id = GUI_CONTROLLER_COMPONENT;
}

void GUIControllerComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name.substr(0, 6) == "Action")
		{
			auto action = stringToInputAction(property->value);
			auto comp = new GUIInputComponent(m_gameObject, this);
			comp->init(action);
			registerInput(comp);
		}
	}
	m_mapObject = nullptr;
}

void GUIControllerComponent::activate()
{
}

