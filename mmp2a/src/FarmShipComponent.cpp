#include "stdafx.h"
#include "FarmShipComponent.h"

#include "BasicAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

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
	Stats baseStats;

	baseStats.attack = 5;
	baseStats.defense = 10;
	baseStats.life = 20;

	baseStats.movement = 7;

	m_baseStats = baseStats;
	m_bonusStats = Stats();

	IAbilityComponent* attack = new BasicAttackAbilityComponent();
	IAbilityComponent* farm = new FarmAbilityComponent();

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FarmShipComponent::initTmxData()
{
	ShipComponent::initTmxData();

	m_mapObject = nullptr;
}