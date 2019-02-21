#include "stdafx.h"
#include "IGameComponent.h"

IGameComponent::IGameComponent(GameObject* gameObject)
	: m_gameObject(gameObject)
{
	m_mapObject = nullptr;
}

IGameComponent::IGameComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: m_gameObject(gameObject)
	, m_mapObject(&mapObject)
{
}
