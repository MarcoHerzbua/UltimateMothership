#include "stdafx.h"
#include "IAbilityComponent.h"

#include "BasicAttackAbilityComponent.h"
#include "UltimateAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"
#include "GameObject.h"

IAbilityComponent::IAbilityComponent(GameObject * gameObject)
	: m_gameObject(gameObject)
{
	m_mapObject = nullptr;
	m_id = ABILITY;
}

IAbilityComponent::IAbilityComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: m_gameObject(gameObject)
	, m_mapObject(&mapObject)
{
	m_id = ABILITY;
}

void IAbilityComponent::exit()
{
}

void IAbilityComponent::initTmxData()
{
}

void IAbilityComponent::addTarget(Target t)
{
	m_targets.push_back(t);
}

void IAbilityComponent::resolveTargets()
{
	for (auto t : m_targets)
	{
		useAbility(t);
	}
	clearTargets();
}

void IAbilityComponent::clearTargets()
{
	m_targets.clear();
}

ShipComponent* IAbilityComponent::getShipFromGameObject(GameObject* g)
{
	ShipComponent* ship;

	auto s = g->findComponents(FIGHTER_SHIP_COMPONENT);
	if (s.size() > 0)
		ship = static_cast<ShipComponent*>(s[0]);
	else
	{
		s = g->findComponents(MOTHER_SHIP_COMPONENT);
		if (s.size() > 0)
			ship = static_cast<ShipComponent*>(s[0]);
		else
		{
			s = g->findComponents(FARM_SHIP_COMPONENT);
			if (s.size() > 0)
				ship = static_cast<ShipComponent*>(s[0]);
			else
				return nullptr;
		}
	}

	return ship;
}