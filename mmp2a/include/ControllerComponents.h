#pragma once

#include "stdafx.h"

using namespace std;

enum ControllerComponents
{
	NULL_CONTROLLER_COMPONENT = 0,

	CONTROLLER_COMPONENT,

	AI_CONTROLLER_COMPONENT,
	HUMAN_CONTROLLER_COMPONENT,
	GUI_CONTROLLER_COMPONENT

};

static ControllerComponents stringToControllerComponents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const map<string, ControllerComponents> optionStrings
	{
		{ "controllercomponent",			CONTROLLER_COMPONENT		},
		{ "aicontrollercomponent",			AI_CONTROLLER_COMPONENT		},
		{ "humancontrollercomponent",		HUMAN_CONTROLLER_COMPONENT	},
		{ "guicontrollercomponent",			GUI_CONTROLLER_COMPONENT	}
	};

	auto itr = optionStrings.find(s);

	if (itr != optionStrings.end())
		return itr->second;

	return NULL_CONTROLLER_COMPONENT;
}