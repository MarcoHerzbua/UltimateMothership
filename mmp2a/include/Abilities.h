#pragma once

#include "stdafx.h"

using namespace std;

enum Abilities
{
	NULL_ABILITY = 0,

	ATTACK_ABILITY,
	FARM_ABILITY,

	BASIC_ATTACK_ABILITY,
	ULTIMATE_ATTACK_ABILITY,
};

static Abilities stringToAbilities(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const map<string, Abilities> optionStrings
	{
		{ "attackability",				ATTACK_ABILITY			},
		{ "farmability",				FARM_ABILITY			},
		{ "basicattackability",			BASIC_ATTACK_ABILITY	},
		{ "ultimateattackability",		ULTIMATE_ATTACK_ABILITY	}
	};

	auto itr = optionStrings.find(s);

	if (itr != optionStrings.end())
		return itr->second;

	return NULL_ABILITY;
}