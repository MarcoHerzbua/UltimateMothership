#pragma region include

#include "stdafx.h"
#include "ControllerComponent.h"

#include "IInputComponent.h"

#include "SteeringComponent.h"

#include "GameObject.h"

#pragma endregion

ControllerComponent::ControllerComponent(GameObject * gameObject, SteeringComponent* steeringComponent)
	: IControllerComponent(gameObject, steeringComponent)
{
	m_id = CONTROLLER_COMPONENT;
}
ControllerComponent::ControllerComponent(GameObject * gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject)
	: IControllerComponent(gameObject, steeringComponent, mapObject)
{
	m_id = CONTROLLER_COMPONENT;
}

void ControllerComponent::update(const float deltaTimeSeconds)
{
	for (auto i : m_inputs)
	{
		i->update(deltaTimeSeconds);
	}
}

void ControllerComponent::exit()
{
	for (auto i : m_inputs)
	{
		i->exit();
		delete i;
	}
	m_inputs.clear();
}

void ControllerComponent::registerInput(IInputComponent * i)
{
	m_inputs.push_back(i);
}
void ControllerComponent::removeInput(InputComponents iId)
{
	auto iIti = findInputIterator(iId);

	if (iIti != m_inputs.end())
	{
		m_inputs.erase(iIti);
		(*iIti)->exit();
		delete (*iIti);
	}
}
IInputComponent * ControllerComponent::findInput(InputComponents iId)
{
	auto iIti = findInputIterator(iId);

	if (iIti != m_inputs.end()) return *iIti;

	return nullptr;
}
vector<IInputComponent*>::iterator ControllerComponent::findInputIterator(const InputComponents iId)
{
	for (auto iIti = m_inputs.begin(); iIti != m_inputs.end(); iIti++)
	{
		if ((*iIti)->getId() == iId) return iIti;
	}

	return m_inputs.end();
}

