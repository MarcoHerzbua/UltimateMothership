#pragma once

#include "stdafx.h"
using namespace std;

enum GameObjects
{
	NULL_OBJECT = 0,

	P1_FIGHTER_OBJECT,
	P1_FARMER_OBJECT,
	P1_MOTHER_OBJECT,
	P2_FIGHTER_OBJECT,
	P2_FARMER_OBJECT,
	P2_MOTHER_OBJECT,
	CURSOR_OBJECT,
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
		{ "p0fighter",		P1_FIGHTER_OBJECT			},
		{ "p1fighter",		P2_FIGHTER_OBJECT			},
		{ "p0farm",			P1_FARMER_OBJECT			},
		{ "p1farm",			P2_FARMER_OBJECT			},
		{ "p0mother",		P1_MOTHER_OBJECT			},
		{ "p1mother",		P2_MOTHER_OBJECT			},
		{ "camera",			CAMERA_OBJECT			},
		{ "tilemap",		TILEMAP_OBJECT			},
		{ "exittext",		EXIT_TEXT_OBJECT		},
		{ "continuetext",	CONTINUE_TEXT_OBJECT	},
		{ "cursor",			CURSOR_OBJECT	},
		{ "gui",			GUI_OBJECT					}
	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_OBJECT;
}