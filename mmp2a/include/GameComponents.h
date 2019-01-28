#pragma once

#include "stdafx.h"

using namespace std;

enum GameComponents
{
	NULL_COMPONENT = 0,

	COMPONENT,

	CAMERA_COMPONENT,

	RENDER_COMPONENT,
	SPRITE_RENDER_COMPONENT,
	SHAPE_RENDER_COMPONENT,
	GUI_RENDER_COMPONENT,
	GUI_BUTTON_COMPONENT,
	LAYER_RENDER_COMPONENT,
	DEBUG_GEOMETRY_RENDER_COMPONENT,
	NODE_GRAPH_RENDER_COMPONENT,

	RIGID_BODY_COMPONENT,
	COLLISION_COMPONENT,
	POINT_COUNTER_COMPONENT,
	OBSERVER_COMPONENT,
	DEATH_ZONE_COMPONENT,
	STEERING_COMPONENT,

};

static GameComponents stringToGameComponents(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, GameComponents> optionStrings
	{
		{ "component",						COMPONENT							},

		{ "cameracomponent",				CAMERA_COMPONENT					},

		{ "rendercomponent",				RENDER_COMPONENT					},
		{ "spriterendercomponent",			SPRITE_RENDER_COMPONENT				},
		{ "shaperendercomponent",			SHAPE_RENDER_COMPONENT				},
		{ "guirendercomponent",				GUI_RENDER_COMPONENT				},
		{ "guibuttoncomponent",				GUI_BUTTON_COMPONENT				},
		{ "layerrendercomponent",			LAYER_RENDER_COMPONENT				},
		{ "debuggeometryrendercomponent",	DEBUG_GEOMETRY_RENDER_COMPONENT		},
		{ "nodegraphcomponent",				NODE_GRAPH_RENDER_COMPONENT			},

		{ "rigidbodycomponent",				RIGID_BODY_COMPONENT				},
		{ "collisioncomponent",				COLLISION_COMPONENT					},
		{ "pointcountercomponent",			POINT_COUNTER_COMPONENT				},
		{ "observercomponent",				OBSERVER_COMPONENT					},
		{ "deathzonecomponent",				DEATH_ZONE_COMPONENT				},
		{ "steeringcomponent",				STEERING_COMPONENT					}

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return NULL_COMPONENT;
}