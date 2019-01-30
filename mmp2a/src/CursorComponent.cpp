#include "stdafx.h"
#include "CursorComponent.h"

#include "GameObject.h"
#include "SteeringComponent.h"
#include "PlayerManager.h"

CursorComponent::CursorComponent(GameObject* gameObject)
	: IGameComponent(gameObject)
{
	m_id = CURSOR_COMPONENT;
}

CursorComponent::CursorComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = CURSOR_COMPONENT;
}

void CursorComponent::update(const float deltaTimeSeconds)
{
}

void CursorComponent::exit()
{
}

void CursorComponent::initTmxData()
{
	auto s = static_cast<SteeringComponent*>(m_gameObject->findComponents(STEERING_COMPONENT)[0]);
	PlayerManager::getInstance().registerCursor(s);
}
