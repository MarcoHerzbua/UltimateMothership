#pragma once

#include "stdafx.h"
#include "Direction.h"
using namespace std;

enum GameEvents
{
	START_GAME_EVENT,
	EXIT_GAME_EVENT,
	SHOW_CREDITS_EVENT,
	SHOW_CONTROLS_EVENT,
	BACK_TO_MENU_EVENT,
	NAVIGATE_UP_EVENT,
	NAVIGATE_DOWN_EVENT,
	NAVIGATE_LEFT_EVENT,
	NAVIGATE_RIGHT_EVENT,
	CONFIRM_EVENT,
	UPDATE_SHIPSTATS_EVENT,
	UPDATE_PLAYERSTATS_EVENT,
	UPDATE_BUTTONMAP_EVENT,
	UPDATE_POPUP_EVENT,
	TOGGLE_POPUP_EVENT,
	GAMEPLAYSTATE_CHANGE_EVENT,
	GAMEPLAYSTATE_END_TURN_EVENT,
	TOGGLE_LABEL_TEXT_EVENT,
	TOGGLE_GAME_OVER_EVENT,

	NULL_GAME_EVENT
};

static GameEvents stringToGameEvents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, GameEvents> optionStrings
	{
		{ "startgameevent",					START_GAME_EVENT						},
		{ "showcreditsevent",				SHOW_CREDITS_EVENT						},
		{ "showcontrolsevent",				SHOW_CONTROLS_EVENT						},
		{ "backtomenuevent",				BACK_TO_MENU_EVENT						},
		{ "navigateupevent",				NAVIGATE_UP_EVENT						},
		{ "navigatedownevent",				NAVIGATE_DOWN_EVENT						},
		{ "navigateleftevent",				NAVIGATE_LEFT_EVENT						},
		{ "navigaterightevent",				NAVIGATE_RIGHT_EVENT					},
		{ "exitgameevent",					EXIT_GAME_EVENT							},
		{ "confirmevent",					CONFIRM_EVENT							}

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_GAME_EVENT;
}

static GameEvents inputToGameEvents(InputActions s) {

	static const std::map<InputActions, GameEvents> optionStrings
	{
		{ MOVE_UP_ACTION,				NAVIGATE_UP_EVENT						},
		{ MOVE_DOWN_ACTION,				NAVIGATE_DOWN_EVENT						},
		{ MOVE_LEFT_ACTION,				NAVIGATE_LEFT_EVENT						},
		{ MOVE_RIGHT_ACTION,			NAVIGATE_RIGHT_EVENT					},
		{ A_BUTTON_ACTION,				CONFIRM_EVENT							},
		{ ESCAPE_ACTION,				EXIT_GAME_EVENT						}

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_GAME_EVENT;
}