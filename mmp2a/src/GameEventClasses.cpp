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
