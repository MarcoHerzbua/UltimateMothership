#pragma region include
#pragma once
#include "stdafx.h"

#include "IGameEvent.h"
#include "GameEvents.h"

class IGameplayState;
class ShipComponent;

using namespace std;
using namespace sf;

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
	UpdatePlayerStatsEvent(int playerIdx);
	int m_playerIdx;
};

class UpdateButtonMapEvent : public virtual IGameEvent
{
public:
	UpdateButtonMapEvent(vector<sf::String> buttonMap);
	vector<sf::String> m_buttonMap;
};

class TogglePopupEvent : public virtual IGameEvent
{
public:
	TogglePopupEvent(bool setVisible);
	bool m_isVisible;
};

class GameplayStateChangeEvent : public virtual IGameEvent
{
public:
	GameplayStateChangeEvent(IGameplayState * prev, IGameplayState * next);
	IGameplayState * m_prev;
	IGameplayState * m_next;
};

class UpdatePopupEvent : public virtual IGameEvent
{
public:
	UpdatePopupEvent(std::string text);
	string m_text;
};

class GameplayEndTurnEvent : public virtual IGameEvent
{
public:
	GameplayEndTurnEvent();
};

class ToggleLabelTextEvent : public virtual IGameEvent
{
public:
	ToggleLabelTextEvent(bool setVisible, int playeridx);
	bool m_isVisible;
	int m_playerIdx;
};

class ToggleGameOverEvent : public virtual IGameEvent
{
public:
	ToggleGameOverEvent(int winPlayerIdx);
	int m_winPlayerIdx;
};

class ShowCreditsEvent : public virtual IGameEvent
{
public:
	ShowCreditsEvent();
};

class BackToMenuEvent : public virtual IGameEvent
{
public:
	BackToMenuEvent();
};

class ShowControlsEvent : public virtual IGameEvent
{
public:
	ShowControlsEvent();
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
	case(SHOW_CREDITS_EVENT):
		return new ShowCreditsEvent();
		break;
	case(SHOW_CONTROLS_EVENT):
		return new ShowControlsEvent();
		break;
	case(BACK_TO_MENU_EVENT):
		return new BackToMenuEvent();
		break;
	default:
		return nullptr;
	}
}
