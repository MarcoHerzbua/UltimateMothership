#pragma once

#include "stdafx.h"
using namespace std;

enum GameObjects
{
	NULL_OBJECT = 0,

	// PLAYER1_OBJECT,
	// PLAYER2_OBJECT,

	CAMERA_OBJECT,

	TILEMAP_OBJECT,
	GUI_OBJECT,

	CONTINUE_TEXT_OBJECT,
	EXIT_TEXT_OBJECT,

};


static GameObjects stringToGameObjects(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, GameObjects> optionStrings
	{
		// { "player1",		PLAYER1_OBJECT			},
		// { "player2",		PLAYER2_OBJECT			},
		{ "camera",			CAMERA_OBJECT			},
		{ "tilemap",		TILEMAP_OBJECT			},
		{ "exittext",		EXIT_TEXT_OBJECT		},
		{ "continuetext",	CONTINUE_TEXT_OBJECT	},
		{ "gui",			GUI_OBJECT					}
	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_OBJECT;
}