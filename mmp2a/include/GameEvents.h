#pragma once

#include "stdafx.h"
#include "Direction.h"
using namespace std;

enum GameEvents
{
	START_GAME_EVENT,
	EXIT_GAME_EVENT,
	NAVIGATE_UP_EVENT,
	NAVIGATE_DOWN_EVENT,
	NAVIGATE_LEFT_EVENT,
	NAVIGATE_RIGHT_EVENT,
	NULL_GAME_EVENT
};

static GameEvents stringToGameEvents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, GameEvents> optionStrings
	{
		{ "startgameevent",					START_GAME_EVENT						},
		{ "navigateupevent",				NAVIGATE_UP_EVENT						},
		{ "navigatedownevent",				NAVIGATE_DOWN_EVENT						},
		{ "navigateleftevent",				NAVIGATE_LEFT_EVENT						},
		{ "navigaterightevent",				NAVIGATE_RIGHT_EVENT					},
		{ "exitgameevent",					EXIT_GAME_EVENT							}

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_GAME_EVENT;
}

static GameEvents directionToGameEvents(Direction s) {

	static const std::map<Direction, GameEvents> optionStrings
	{
		{ UP,				NAVIGATE_UP_EVENT						},
		{ DOWN,				NAVIGATE_DOWN_EVENT						},
		{ LEFT,				NAVIGATE_LEFT_EVENT						},
		{ RIGHT,			NAVIGATE_RIGHT_EVENT					}

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_GAME_EVENT;
}