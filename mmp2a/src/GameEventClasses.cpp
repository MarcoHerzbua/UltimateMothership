#include "stdafx.h"
#include "GameEventClasses.h"

StartGameEvent::StartGameEvent()
{
	m_id = START_GAME_EVENT;
}

ExitGameEvent::ExitGameEvent()
{
	m_id = EXIT_GAME_EVENT;
}

MenuNavigationEvent::MenuNavigationEvent(GameEvents ev)
{
	m_id = ev;
}

UpdateShipStatsEvent::UpdateShipStatsEvent(ShipComponent * cmp)
{
	m_id = UPDATE_SHIPSTATS_EVENT;
	m_shipComponent = cmp;
}

UpdatePlayerStatsEvent::UpdatePlayerStatsEvent(int playerIdx)
{
	m_id = UPDATE_PLAYERSTATS_EVENT;
	m_playerIdx = playerIdx;
}

UpdateButtonMapEvent::UpdateButtonMapEvent(vector<sf::String> buttonMap)
{
	m_id = UPDATE_BUTTONMAP_EVENT;
	m_buttonMap = buttonMap;
}

TogglePopupEvent::TogglePopupEvent(bool isVisible)
{
	m_id = TOGGLE_POPUP_EVENT;
	m_isVisible = isVisible;
}

GameplayStateChangeEvent::GameplayStateChangeEvent(IGameplayState * prev, IGameplayState * next)
{
	m_id = GAMEPLAYSTATE_CHANGE_EVENT;
	m_prev = prev;
	m_next = next;
}

UpdatePopupEvent::UpdatePopupEvent(std::string text)
{
	m_id = UPDATE_POPUP_EVENT;
	m_text = text;
}

GameplayEndTurnEvent::GameplayEndTurnEvent()
{
	m_id = GAMEPLAYSTATE_END_TURN_EVENT;
}

ToggleLabelTextEvent::ToggleLabelTextEvent(bool setVisible, int playerIdx)
{
	m_id = TOGGLE_LABEL_TEXT_EVENT;
	m_isVisible = setVisible;
	m_playerIdx = playerIdx;

}

ToggleGameOverEvent::ToggleGameOverEvent(int winPlayerIdx)
{
	m_id = TOGGLE_GAME_OVER_EVENT;
	m_winPlayerIdx = winPlayerIdx;
}
