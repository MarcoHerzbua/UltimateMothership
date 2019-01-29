#pragma once

#include "stdafx.h"

#include "NLTmxMap.h"
#include "Abilities.h"

class GameObject;

class IAbilityComponent
{
public:
	IAbilityComponent() = default;
	IAbilityComponent(GameObject* gameObject);
	IAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~IAbilityComponent() = default;

	virtual void exit();

	virtual void update(const float deltaTime) = 0;

	virtual void initTmxData();

	Abilities getId() { return m_id; };
	GameObject* getGameObjectPtr() { return m_gameObject; };

protected:
	Abilities m_id;
	GameObject* m_gameObject;
	NLTmxMapObject* m_mapObject;
};