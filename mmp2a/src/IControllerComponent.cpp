#pragma region include

#include "stdafx.h"
#include "IControllerComponent.h"
#pragma endregion

IControllerComponent::IControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent)
	: m_gameObject(gameObject)
	, m_steeringComponent(steeringComponent)
{
	m_mapObject = nullptr;
}

IControllerComponent::IControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject)
	: m_gameObject(gameObject)
	, m_steeringComponent(steeringComponent)
	, m_mapObject(&mapObject)
{
}
