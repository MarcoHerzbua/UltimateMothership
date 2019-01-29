#include "stdafx.h"
#include "UltimateAttackAbilityComponent.h"

UltimateAttackAbilityComponent::UltimateAttackAbilityComponent(GameObject * gameObject)
	: AttackAbilityComponent(gameObject)
{
	m_id = ULTIMATE_ATTACK_ABILITY;
}

UltimateAttackAbilityComponent::UltimateAttackAbilityComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: AttackAbilityComponent(gameObject, mapObject)
{
	m_id = ULTIMATE_ATTACK_ABILITY;
}

void UltimateAttackAbilityComponent::update(const float deltaTime)
{
}
