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

UpdatePlayerStatsEvent::UpdatePlayerStatsEvent()
{
	m_id = UPDATE_PLAYERSTATS_EVENT;
}
