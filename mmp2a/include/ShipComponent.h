	#pragma once

#include "stdafx.h"
#include "IGameComponent.h"

#include "Abilities.h"

#include "Stats.h"

class IAbilityComponent;
class GameObject;

class ShipComponent : public IGameComponent
{
public:
	ShipComponent() = default;
	ShipComponent(GameObject* gameObject);
	ShipComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~ShipComponent() = default;

	void exit() override;
	
	virtual void update(const float deltaTime) override {};

	virtual void initBaseStats() = 0;

	virtual void initTmxData();


	void addTarget(Target t, Abilities a);
	void resolveTargets();
	void resolveTargets(Abilities a);

	// =============================================================
	
	Stats getBaseStats() { return m_baseStats; };
	Stats getCurrentStats() { return m_currentStats; };
	
	// =============================================================

	int getCurrentMovement() { return m_currentStats.movement; };

	void decreasMovement() { if (canMove()) m_currentStats.movement--; };
	void decreasMovement(int amount) { if (canMove(amount)) m_currentStats.movement -= amount; };
	bool canMove() { return m_currentStats.movement > 0; };
	bool canMove(int amount) { return m_currentStats.movement - amount >= 0; };

	void resetMovement() { m_currentStats.movement = m_baseStats.movement; };

	// =============================================================

	// basedamage of ability, attack of other player
	void getDamage(int baseDamage, int attack); //calculated damage gets subtracted from life
	int calcDamage(int baseDamage, int attack); //only for calculation of damage

	void restoreLife(int amount);

	bool isDead() { return m_currentStats.life <= 0; };
	void die();


	IAbilityComponent * getAbilityComponent(Abilities a);
	string getName() { return m_name; };

protected:
	Stats m_currentStats;
	Stats m_baseStats;
	string m_name;

	map<Abilities, IAbilityComponent*> m_abilities;

	void clearTargets();
};