#include "stdafx.h"
#include "ShipComponent.h"

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
		// TODO do as soon as possible
		/*ability.second()->exit();
		delete ability.second();*/
	}

	m_abilities.clear();
}

void ShipComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}

void ShipComponent::getDamage(int baseDamage, int attack)
{
	// formula used to calculate damage
	// Damage = Base Damage * 2 ^ ((Attack - Defense)/Doubling Rate)

	float doublingRate = 25; //TODO chagne doublingRate according to tests

	int damage = (float)(attack * (pow(2, ((attack - m_currentStats.defense) / doublingRate))));

	m_currentStats.life -= m_currentStats.life - damage >= 0 ? damage : m_currentStats.life;
}

void ShipComponent::restoreLife(int amount)
{
	if (m_currentStats.life + amount <= m_baseStats.life)
		m_currentStats.life += amount;
}
