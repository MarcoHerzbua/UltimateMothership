#include "stdafx.h"
#include "IAbilityComponent.h"

IAbilityComponent::IAbilityComponent(GameObject * gameObject)
	: m_gameObject(gameObject)
{
	m_mapObject = nullptr;
	m_id = ABILITY;

	m_range = 1;
}

IAbilityComponent::IAbilityComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: m_gameObject(gameObject)
	, m_mapObject(&mapObject)
{
	m_id = ABILITY;
	
	m_range = 1;
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

