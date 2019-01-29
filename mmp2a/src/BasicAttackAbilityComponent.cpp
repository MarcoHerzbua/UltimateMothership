#include "stdafx.h"
#include "BasicAttackAbilityComponent.h"

BasicAttackAbilityComponent::BasicAttackAbilityComponent(GameObject* gameObject)
	: AttackAbilityComponent(gameObject)
{
	m_id = BASIC_ATTACK_ABILITY;
}

BasicAttackAbilityComponent::BasicAttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: AttackAbilityComponent(gameObject, mapObject)
{
	m_id = BASIC_ATTACK_ABILITY;
}

void BasicAttackAbilityComponent::update(const float deltaTime)
{
}
