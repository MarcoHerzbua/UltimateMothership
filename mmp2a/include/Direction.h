#pragma once

#include "stdafx.h"

#include "InputActions.h"

using namespace std;
using namespace sf;

enum Direction
{
	CENTER = 0,
	
	UP,
	RIGHT,
	DOWN,
	LEFT,

};

static sf::Vector2f directionToVec2f(Direction d)
{
	switch (d)
	{
	case UP:		return Vector2f( 0,  1);
	case RIGHT:		return Vector2f(-1,  0);
	case DOWN:		return Vector2f( 0, -1);
	case LEFT:		return Vector2f( 1,  0);
	default:		return Vector2f( 0,  0);
	}
}

static Direction inputActionsToDirection(InputActions i)
{
	switch (i)
	{
	case MOVE_UP_ACTION:		return UP;
	case MOVE_RIGHT_ACTION:		return RIGHT;
	case MOVE_DOWN_ACTION:		return DOWN;
	case MOVE_LEFT_ACTION:		return LEFT;
	default:					return CENTER;
	}
}

static Direction stringToDirection(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	static const std::map<std::string, Direction> optionStrings
	{
		{ "up",		UP		},
		{ "right",	RIGHT	},
		{ "down",	DOWN	},
		{ "left",	LEFT	},

	};

	auto itr = optionStrings.find(s);
	if (itr != optionStrings.end()) {
		return itr->second;
	}
	return CENTER;
}