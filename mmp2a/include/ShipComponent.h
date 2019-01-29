	#pragma once

#include "stdafx.h"
#include "IGameComponent.h"

#include "GameComponents.h"
#include "Abilities.h"

class IAbilityComponent;
class GameObject;

struct Target
{
	GameObject* origin;
	GameObject* target;
};

struct Stats
{
	int attack;
	int defense;

	int life;

	int movement;

	Stats operator+(Stats rhs) 
	{
		*this + rhs;
	}
	Stats operator+(Stats* rhs)
	{
		Stats result;

		result.attack = this->attack + rhs->attack;
		result.defense = this->defense + rhs->defense;
		result.life = this->life + rhs->life;

		result.movement = this->movement + rhs->movement;

		return result;
	}
	Stats operator-(Stats rhs)
	{
		*this - rhs;
	}
	Stats operator-(Stats* rhs)
	{
		Stats result;

		result.attack = this->attack - rhs->attack;
		result.defense = this->defense - rhs->defense;
		result.life = this->life - rhs->life;

		result.movement = this->movement - rhs->movement;

		return result;
	}

	bool operator==(Stats* rhs)
	{
		return (this->attack == rhs->attack) 
			&& (this->defense == rhs->defense) 
			&& (this->life == rhs->life)
			&& (this->movement == rhs->movement) ;
	}
	bool operator!=(Stats* rhs)
	{
		return !(this == rhs);
	}
};

class ShipComponent : public IGameComponent
{
public:
	ShipComponent() = default;
	ShipComponent(GameObject* gameObject);
	ShipComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~ShipComponent() = default;

	void exit() override;
	
	virtual void update(const float deltaTime) override {};

	virtual void initBaseStats() {};

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

	int getCurrentRessources() { return m_currentRessources; };
	int getTotalRessources() { return m_totalRessources; };

	void increaseRessources() { m_currentRessources++; m_totalRessources++; };
	void increaseRessources(int amount) { m_currentRessources += amount; m_totalRessources++; };
	void decreaseRessources(int amount) { m_currentRessources -= amount; };

	// =============================================================

	// basedamage of ability, attack of other player
	void getDamage(int baseDamage, int attack);

	void restoreLife(int amount);

	bool isDead() { return m_currentStats.life <= 0; };

protected:
	int m_totalRessources;
	int m_currentRessources;

	Stats m_currentStats;
	Stats m_baseStats;

	map<Abilities, IAbilityComponent*> m_abilities;

	void clearTargets();
};