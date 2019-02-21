#include "stdafx.h"
#include "FighterShipComponent.h"

#include "IAbilityComponent.h"
#include "BasicAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

#include "Stats.h"

FighterShipComponent::FighterShipComponent(GameObject * gameObject)
	: ShipComponent(gameObject)
{
	m_id = FIGHTER_SHIP_COMPONENT;
	//initBaseStats();
}

FighterShipComponent::FighterShipComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: ShipComponent(gameObject, mapObject)
{
	m_id = FIGHTER_SHIP_COMPONENT;
	//initBaseStats();
}

void FighterShipComponent::update(const float deltaTime)
{
	//Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(this));
}

void FighterShipComponent::initBaseStats()
{
	m_baseStats.attack = 30;
	m_baseStats.defense = 5;
	m_baseStats.life = 10;
	m_baseStats.movement = 12;

	m_currentStats.attack = 30;
	m_currentStats.defense = 5;
	m_currentStats.life = 10;
	m_currentStats.movement = 12;

	IAbilityComponent* attack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FighterShipComponent::initTmxData()
{
	ShipComponent::initTmxData();

	if (!m_mapObject)
		return;


	m_mapObject = nullptr;
}
