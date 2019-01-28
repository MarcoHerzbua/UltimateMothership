#pragma once

#include "stdafx.h"

using namespace std;

enum LayerComponents
{
	NULL_LAYER = 0,

	OCLUSION_LAYER,
	FOREGROUND_LAYER,
	BACKGROUND_LAYER,
	NODE_GRID_LAYER,

};

static LayerComponents stringToLayerComponents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, LayerComponents> optionStrings
	{
		{ "oclusion",		OCLUSION_LAYER,		},
		{ "foreground",		FOREGROUND_LAYER,	},
		{ "background",		BACKGROUND_LAYER,	},
		{ "nodegrid",		NODE_GRID_LAYER,	}
	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_LAYER;
}