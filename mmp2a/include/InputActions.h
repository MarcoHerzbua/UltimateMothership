#pragma once

#include "stdafx.h"
using namespace std;

enum InputActions
{
	NULL_ACTION = 0,

	EXIT_ACTION,
	CONFIRM_ACTION,

	X_BUTTON_ACTION,
	B_BUTTON_ACTION,
	Y_BUTTON_ACTION,
	A_BUTTON_ACTION,

	MOVE_LEFT_ACTION,
	MOVE_RIGHT_ACTION,
	MOVE_UP_ACTION,
	MOVE_DOWN_ACTION,

	SWITCH_HUMAN_AI,

	NEXT_UNIT_ACTION,
	NEXT_PLAYER_ACTION,

};

static InputActions stringToInputAction(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, InputActions> optionStrings
	{
		{ "exit",				EXIT_ACTION				},
		{ "switchstate",		CONFIRM_ACTION		},

		{ "moveleft",			MOVE_LEFT_ACTION		},
		{ "moveright",			MOVE_RIGHT_ACTION		},
		{ "moveup",				MOVE_UP_ACTION			},
		{ "movedown",			MOVE_DOWN_ACTION		},

		{ "switchhumanai",		SWITCH_HUMAN_AI			},

		{ "nextunit",			NEXT_UNIT_ACTION		},
		{ "nextplayer",			NEXT_PLAYER_ACTION		},


	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_ACTION;
}