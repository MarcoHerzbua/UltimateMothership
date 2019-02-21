#include "stdafx.h"
#include "ShipComponent.h"

#include "IAbilityComponent.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SteeringComponent.h"
#include "PlayerManager.h"
#include "Node.h"
#include "NLTmxMap.h"


ShipComponent::ShipComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	m_id = SHIP_COMPONENT;
}

ShipComponent::ShipComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = SHIP_COMPONENT;
}

void ShipComponent::exit()
{
	for (auto ability : m_abilities)
	{
		ability.second->exit();
		delete ability.second;
	}
	m_abilities.clear();
}

void ShipComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "ShipName")
		{
			m_name = property->value;
		}
	}

	m_mapObject = nullptr;
}

void ShipComponent::addTarget(Target t, Abilities a)
{
	m_abilities[a]->addTarget(t);
}

void ShipComponent::resolveTargets()
{
	for (auto ability : m_abilities)
	{
		ability.second->resolveTargets();
	}
}

void ShipComponent::resolveTargets(Abilities a)
{
	m_abilities[a]->resolveTargets();
}

void ShipComponent::getDamage(int baseDamage, int attack)
{
	int damage = calcDamage(baseDamage, attack);

	m_currentStats.life -= m_currentStats.life - damage >= 0 ? damage : m_currentStats.life;

	if (isDead())
		die();
}

int ShipComponent::calcDamage(int baseDamage, int attack)
{
	// formula used to calculate damage
	// Damage = Base Damage * 2 ^ ((Attack - Defense)/Doubling Rate)

	float doublingRate = 12;

	return (float)(baseDamage * (pow(2, ((attack - m_currentStats.defense) / doublingRate))));
}

void ShipComponent::restoreLife(int amount)
{
	if (m_currentStats.life + amount <= m_baseStats.life)
		m_currentStats.life += amount;
}

IAbilityComponent * ShipComponent::getAbilityComponent(Abilities a)
{
	auto ability = m_abilities.find(a);

	if (ability != m_abilities.end())
		return (*ability).second;
	
	return nullptr;
}

void ShipComponent::die()
{
	if (this == PlayerManager::getInstance().getActiveShip())
		PlayerManager::getInstance().activateNextUnit();

	GameObjectManager::getInstance().markForDelete(m_gameObject);

	static_cast<SteeringComponent*>(m_gameObject->findComponents(STEERING_COMPONENT)[0])->getCurrentNode()->removeGameObject(m_gameObject);
}

void ShipComponent::clearTargets()
{
	for (auto ability : m_abilities)
	{
		ability.second->clearTargets();
	}
}
