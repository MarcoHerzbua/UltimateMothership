#pragma region include
#pragma once
#include "stdafx.h"
#include "IGameEvent.h"
#include "Direction.h"
#include "ShipComponent.h"
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

class MenuNavigationEvent : public virtual IGameEvent
{
public: 
	MenuNavigationEvent(GameEvents ev);
};

class UpdateShipStatsEvent : public virtual IGameEvent
{
public:
	UpdateShipStatsEvent(ShipComponent * cmp);
	ShipComponent * m_shipComponent;
};

class UpdatePlayerStatsEvent : public virtual IGameEvent
{
public:
	UpdatePlayerStatsEvent(int resources);
	int m_resources;
};

class UpdateButtonMapEvent : public virtual IGameEvent
{
public:
	UpdateButtonMapEvent(vector<sf::String> buttonMap);
	vector<sf::String> m_buttonMap;
};

//THis method gets called when Buttons with Events are created in Tiled (Action_ = ...)
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
