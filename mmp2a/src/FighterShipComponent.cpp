#include "stdafx.h"
#include "FighterShipComponent.h"

#include "IAbilityComponent.h"
#include "BasicAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

#include "Stats.h"

#include "Eventbus.h"
#include "GameEventClasses.h"

FighterShipComponent::FighterShipComponent(GameObject * gameObject)
	: ShipComponent(gameObject)
{
	m_id = FIGHTER_SHIP_COMPONENT;
	//initBaseStats();
	m_baseStats.attack = 10;
	m_baseStats.defense = 5;
	m_baseStats.life = 10;

	m_baseStats.movement = 10;

	m_currentStats = m_baseStats;

	IAbilityComponent* attack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

FighterShipComponent::FighterShipComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: ShipComponent(gameObject, mapObject)
{
	m_id = FIGHTER_SHIP_COMPONENT;
	//initBaseStats();
	m_baseStats.attack = 10;
	m_baseStats.defense = 5;
	m_baseStats.life = 10;

	m_baseStats.movement = 10;

	m_currentStats = m_baseStats;

	IAbilityComponent* attack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FighterShipComponent::update(const float deltaTime)
{
	//Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(this));
}

void FighterShipComponent::initBaseStats()
{
	m_baseStats.attack = 10;
	m_baseStats.defense = 5;
	m_baseStats.life = 10;

	m_baseStats.movement = 10;

	m_currentStats = m_baseStats;

	IAbilityComponent* attack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FighterShipComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}
