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

void UltimateAttackAbilityComponent::useAbility(Target t)
{
	ShipComponent* target = getShipFromGameObject(t.target);
	ShipComponent* origin = getShipFromGameObject(t.origin);

	Stats targetStats = target->getCurrentStats();
	Stats originStats = origin->getCurrentStats();

	target->getDamage(getBaseDamage(), originStats.attack);

	if (target->isDead())
	{
		//TODO Player origin wins
	}
}
