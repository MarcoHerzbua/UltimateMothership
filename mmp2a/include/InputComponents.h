#pragma once

#include "stdafx.h"

using namespace std;

enum InputComponents
{
	NULL_INPUT_COMPONENT = 0,

	HUMAN_INPUT_COMPONENT,
	AI_INPUT_COMPONENT,
	GUI_INPUT_COMPONENT
};

static InputComponents stringToInputComponents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const map<string, InputComponents> optionStrings
	{
		{ "humaninputcomponent",	HUMAN_INPUT_COMPONENT	},
		{ "aiinputcomponent",		AI_INPUT_COMPONENT		},
		{ "guiinputcomponent",		GUI_INPUT_COMPONENT		}
	};

	auto itr = optionStrings.find(s);

	if (itr != optionStrings.end())
		return itr->second;

	return NULL_INPUT_COMPONENT;
}