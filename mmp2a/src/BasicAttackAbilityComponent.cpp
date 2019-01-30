#include "stdafx.h"
#include "BasicAttackAbilityComponent.h"

#include "IGameComponent.h"
#include "SteeringComponent.h"
#include "PlayerManager.h"

#include "ShipComponent.h"


BasicAttackAbilityComponent::BasicAttackAbilityComponent(GameObject* gameObject)
	: AttackAbilityComponent(gameObject)
{
	m_id = BASIC_ATTACK_ABILITY;
	
	m_range = 5;
}

BasicAttackAbilityComponent::BasicAttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: AttackAbilityComponent(gameObject, mapObject)
{
	m_id = BASIC_ATTACK_ABILITY;
	
	m_range = 5;
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

	const int targetPlayerIndex = static_cast<SteeringComponent*>(t.target->findComponents(STEERING_COMPONENT)[0])->getPlayerIndex();
	const int originPlayerIndex = static_cast<SteeringComponent*>(t.origin->findComponents(STEERING_COMPONENT)[0])->getPlayerIndex();

	target->getDamage(getBaseDamage(), originStats.attack);

	if (target->isDead())
	{
		PlayerManager::getInstance().increaseRessources(originPlayerIndex, 5);
	}
	else
	{
		origin->getDamage(getBaseDamage(), targetStats.attack);
		if (origin->isDead())
		{
			PlayerManager::getInstance().increaseRessources(targetPlayerIndex, 5); 
		}
	}
}
