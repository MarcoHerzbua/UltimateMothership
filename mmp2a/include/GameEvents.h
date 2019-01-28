#pragma once

#include "stdafx.h"

using namespace std;

enum GameEvents
{
	START_GAME_EVENT,
	EXIT_GAME_EVENT,
	NULL_GAME_EVENT
};

static GameEvents stringToGameEvents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, GameEvents> optionStrings
	{
		{ "startgameevent",					START_GAME_EVENT						},
		{ "exitgameevent",					EXIT_GAME_EVENT						}

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_GAME_EVENT;
}