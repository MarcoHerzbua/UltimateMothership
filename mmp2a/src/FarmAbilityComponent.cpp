#include "stdafx.h"
#include "FarmAbilityComponent.h"

FarmAbilityComponent::FarmAbilityComponent(GameObject* gameObject)
	:IAbilityComponent(gameObject)
{
	m_id = FARM_ABILITY;
	
	m_range = 1;
}

FarmAbilityComponent::FarmAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	:IAbilityComponent(gameObject, mapObject)
{
	m_id = FARM_ABILITY;
	
	m_range = 1;
}

void FarmAbilityComponent::update(const float deltaTime)
{
}

void FarmAbilityComponent::useAbility(Target t)
{

}
