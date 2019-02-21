#pragma region include

#include "stdafx.h"
#include "HumanControllerComponent.h"

#include "GameObject.h"
#include "SteeringComponent.h"

#include "HumanInputComponent.h"
#include "NLTmxMap.h"
#pragma endregion

HumanControllerComponent::HumanControllerComponent(GameObject * gameObject, SteeringComponent* steeringComponent)
	: ControllerComponent(gameObject, steeringComponent)
{
	m_id = HUMAN_CONTROLLER_COMPONENT;
}
HumanControllerComponent::HumanControllerComponent(GameObject * gameObject, SteeringComponent* steeringComponent, NLTmxMapObject & mapObject)
	: ControllerComponent(gameObject, steeringComponent, mapObject)
{
	m_id = HUMAN_CONTROLLER_COMPONENT;
}

void HumanControllerComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name.substr(0, 6) == "Action")
		{
			auto action = stringToInputAction(property->value);
			auto comp = new HumanInputComponent(m_gameObject, this);
			comp->init(action);
			registerInput(comp);
		}
	}

	m_mapObject = nullptr;
}

void HumanControllerComponent::activate()
{
	cout << "playerIndex: " << m_steeringComponent->getPlayerIndex() << " -- Human active" << endl;
}