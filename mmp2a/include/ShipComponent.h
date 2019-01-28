#pragma once

#include "stdafx.h"
#include "IGameComponent.h"

#include "GameComponents.h"
#include "Abilities.h"

class IAbilityComponent;
class GameObject;

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
	ShipComponent(GameObject* gameObject);
	ShipComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~ShipComponent() = default;

	void exit() override;
	
	virtual void update(const float deltaTime) override = 0;

	virtual void initBaseStats() = 0;

	virtual void initTmxData();

	Stats getTotalStats() { return m_baseStats + m_bonusStats; };

	Stats getBonusStats() { return m_bonusStats; };
	Stats getBaseStats() { return m_baseStats; };

	int getCurrentMovement() { return m_currentMovement; };

	void decreasMovement() { if (canMove()) m_currentMovement--; };
	bool canMove() { return m_currentMovement > 0; };

	void resetMovement() { m_currentMovement = getTotalStats().movement; };

	int getCurrentRessources() { return m_currentRessources; };
	int getTotalRessources() { return m_totalRessources; };

	void increaseRessources() { m_currentRessources++; m_totalRessources++; };
	void removeRessources(int amount) { m_currentRessources -= amount; };

protected:
	int m_currentMovement;
	
	int m_totalRessources;
	int m_currentRessources;

	Stats m_baseStats;
	Stats m_bonusStats;

	map<Abilities, IAbilityComponent*> m_abilities;
};