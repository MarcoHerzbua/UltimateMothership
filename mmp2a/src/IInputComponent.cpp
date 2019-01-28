#include "stdafx.h"
#include "IInputComponent.h"

IInputComponent::IInputComponent(GameObject * gameObject, IControllerComponent * controllerComponent)
	: m_gameObject(gameObject)
	, m_controllerComponent(controllerComponent)
{
	m_mapObject = nullptr;
}

IInputComponent::IInputComponent(GameObject * gameObject, IControllerComponent * controllerComponent, NLTmxMapObject & mapObject)
	: m_gameObject(gameObject)
	, m_controllerComponent(controllerComponent) 
	, m_mapObject(&mapObject)
{
}
