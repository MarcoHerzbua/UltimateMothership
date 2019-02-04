#include "stdafx.h"
#include "AttackAbilityComponent.h"

AttackAbilityComponent::AttackAbilityComponent(GameObject* gameObject)
	: IAbilityComponent(gameObject)
{
	m_id = ATTACK_ABILITY;
}

AttackAbilityComponent::AttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: IAbilityComponent(gameObject, mapObject)
{
	m_id = ATTACK_ABILITY;
}


