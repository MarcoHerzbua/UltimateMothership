#include "stdafx.h"
#include "MotherShipComponent.h"

#include "BasicAttackAbilityComponent.h"
#include "UltimateAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

MotherShipComponent::MotherShipComponent(GameObject * gameObject)
	: ShipComponent(gameObject)
{
	m_id = MOTHER_SHIP_COMPONENT; 
	initBaseStats();
}

MotherShipComponent::MotherShipComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: ShipComponent(gameObject, mapObject)
{
	m_id = MOTHER_SHIP_COMPONENT;
	initBaseStats();
}

void MotherShipComponent::update(const float deltaTime)
{

}

void MotherShipComponent::initBaseStats()
{
	Stats baseStats;

	baseStats.attack = 50;
	baseStats.defense = 50;
	baseStats.life = 100;

	baseStats.movement = 5;

	m_baseStats = baseStats;

	IAbilityComponent* basicAttack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* ultimateAttack = new UltimateAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = basicAttack;
	m_abilities[ULTIMATE_ATTACK_ABILITY] = ultimateAttack;
	m_abilities[FARM_ABILITY] = farm;
}

void MotherShipComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}