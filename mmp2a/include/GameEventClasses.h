#pragma region include
#pragma once
#include "stdafx.h"
#include "IGameEvent.h"
#pragma endregion


class StartGameEvent : public virtual IGameEvent
{
public:
	StartGameEvent();
};

class ExitGameEvent : public virtual IGameEvent
{
public:
	ExitGameEvent();
};

static IGameEvent * createGameEvent(GameEvents event)
{
	switch (event)
	{
	case(START_GAME_EVENT):
		return new StartGameEvent();
		break;
	case(EXIT_GAME_EVENT):
		return new ExitGameEvent();
		break;
	default:
		return nullptr;
	}
}
