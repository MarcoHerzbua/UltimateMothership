#include "stdafx.h"
#include "FarmShipComponent.h"

#include "IAbilityComponent.h"
#include "BasicAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

#include "Stats.h"

FarmShipComponent::FarmShipComponent(GameObject * gameObject)
	: ShipComponent(gameObject)
{
	m_id = FARM_SHIP_COMPONENT;
	initBaseStats();
}

FarmShipComponent::FarmShipComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: ShipComponent(gameObject, mapObject)
{
	m_id = FARM_SHIP_COMPONENT;
	initBaseStats();
}

void FarmShipComponent::update(const float deltaTime)
{

}

void FarmShipComponent::initBaseStats()
{
	m_baseStats.attack = 19;
	m_baseStats.defense = 17;
	m_baseStats.life = 22;
	m_baseStats.movement = 9;

	m_currentStats.attack = 19;
	m_currentStats.defense = 17;
	m_currentStats.life = 22;
	m_currentStats.movement = 9;

	IAbilityComponent* attack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FarmShipComponent::initTmxData()
{
	ShipComponent::initTmxData();

	if (!m_mapObject)
		return;


	m_mapObject = nullptr;
}