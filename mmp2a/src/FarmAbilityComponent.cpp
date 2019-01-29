#include "stdafx.h"
#include "FarmAbilityComponent.h"

FarmAbilityComponent::FarmAbilityComponent(GameObject* gameObject)
	:IAbilityComponent(gameObject)
{
	m_id = FARM_ABILITY;
}

FarmAbilityComponent::FarmAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	:IAbilityComponent(gameObject, mapObject)
{
	m_id = FARM_ABILITY;
}

void FarmAbilityComponent::update(const float deltaTime)
{
}

void FarmAbilityComponent::useAbility(Target t)
{

}
