#include "stdafx.h"
#include "BasicAttackAbilityComponent.h"

#include "ShipComponent.h"
#include "MotherShipComponent.h"
#include "FarmShipComponent.h"
#include "FighterShipComponent.h"
#include "GameObject.h"

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

void BasicAttackAbilityComponent::useAbility(Target t)
{
	ShipComponent* target = getShipFromGameObject(t.target);
	ShipComponent* origin = getShipFromGameObject(t.origin);

	Stats targetStats = target->getCurrentStats();
	Stats originStats = origin->getCurrentStats();

	target->getDamage(getBaseDamage(), originStats.attack);

	if (target->isDead())
	{
		origin->increaseRessources(5);
	}
	else
	{
		origin->getDamage(getBaseDamage(), targetStats.attack);
		if (origin->isDead())
		{
			target->increaseRessources(5);
		}
	}
}
