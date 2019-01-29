#include "stdafx.h"
#include "IAbilityComponent.h"

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