#include "stdafx.h"
#include "MotherShipComponent.h"

#include "IAbilityComponent.h"

#include "BasicAttackAbilityComponent.h"
#include "UltimateAttackAbilityComponent.h"
#include "FarmAbilityComponent.h"

#include "Eventbus.h"
#include "GameEventClasses.h"
#include "PlayerManager.h"

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
	m_baseStats.attack = 27;
	m_baseStats.defense = 20;
	m_baseStats.life = 80;
	m_baseStats.movement = 5;

	m_currentStats.attack = 27;
	m_currentStats.defense = 20;
	m_currentStats.life = 80;
	m_currentStats.movement = 5;

	IAbilityComponent* basicAttack = new BasicAttackAbilityComponent(m_gameObject);
	IAbilityComponent* ultimateAttack = new UltimateAttackAbilityComponent(m_gameObject);
	IAbilityComponent* farm = new FarmAbilityComponent(m_gameObject);

	m_abilities[BASIC_ATTACK_ABILITY] = basicAttack;
	m_abilities[ULTIMATE_ATTACK_ABILITY] = ultimateAttack;
	m_abilities[FARM_ABILITY] = farm;
}

void MotherShipComponent::initTmxData()
{
	ShipComponent::initTmxData();

	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}

void MotherShipComponent::die()
{
	ShipComponent::die();

	Eventbus::getInstance().fireEvent(new ToggleGameOverEvent(PlayerManager::getInstance().getActivePlayer()));
}
