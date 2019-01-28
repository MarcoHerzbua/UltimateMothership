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
	if (!m_gameObject)
		return;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "BonusAttack")
			m_bonusStats.attack += stoi(property->value);
		if (name == "BonusDefense")
			m_bonusStats.defense += stoi(property->value);
		if (name == "BonusLife")
			m_bonusStats.life += stoi(property->value);
		if (name == "BonusMovement")
			m_bonusStats.movement += stoi(property->value);
	}
}
