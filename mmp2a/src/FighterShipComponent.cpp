#include "stdafx.h"
#include "FighterShipComponent.h"
#include "IAbilityComponent.h"

#include "BasicAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

FighterShipComponent::FighterShipComponent(GameObject * gameObject)
	: ShipComponent(gameObject)
{
	m_id = FIGHTER_SHIP_COMPONENT;
	initBaseStats();
}

FighterShipComponent::FighterShipComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: ShipComponent(gameObject, mapObject)
{
	m_id = FIGHTER_SHIP_COMPONENT;
	initBaseStats();
}

void FighterShipComponent::update(const float deltaTime)
{

}

void FighterShipComponent::initBaseStats()
{
	Stats baseStats;

	baseStats.attack = 10;
	baseStats.defense = 5;
	baseStats.life = 10;

	baseStats.movement = 10;

	m_baseStats = baseStats;
	m_bonusStats = Stats();

	IAbilityComponent* attack = new BasicAttackAbilityComponent();
	IAbilityComponent* farm = new FarmAbilityComponent();

	m_abilities[BASIC_ATTACK_ABILITY] = attack;
	m_abilities[FARM_ABILITY] = farm;
}

void FighterShipComponent::initTmxData()
{
	ShipComponent::initTmxData();

	m_gameObject = nullptr;
}
