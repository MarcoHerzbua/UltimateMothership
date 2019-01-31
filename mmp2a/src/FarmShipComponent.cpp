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
	m_baseStats.attack = 5;
	m_baseStats.defense = 10;
	m_baseStats.life = 20;
	m_baseStats.movement = 7;

	m_currentStats.attack = 5;
	m_currentStats.defense = 10;
	m_currentStats.life = 20;
	m_currentStats.movement = 7;

	IAbilityComponent* attack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FarmShipComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}