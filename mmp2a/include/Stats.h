#pragma once
#include "stdafx.h"

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
			&& (this->movement == rhs->movement);
	}
	bool operator!=(Stats* rhs)
	{
		return !(this == rhs);
	}
};