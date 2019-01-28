#pragma region include

#include "stdafx.h"
#include "IGameComponent.h"

// game classes 
#include "Game.h"
#include "GameObject.h"

#pragma endregion

IGameComponent::IGameComponent(GameObject* gameObject)
	: m_gameObject(gameObject)
{
	//m_mapObject = new NLTmxMapObject();
	m_mapObject = nullptr;
}

IGameComponent::IGameComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: m_gameObject(gameObject)
	, m_mapObject(&mapObject)
{
}
