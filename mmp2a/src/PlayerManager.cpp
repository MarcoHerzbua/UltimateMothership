#include "stdafx.h"
#include "PlayerManager.h"

#include "SteeringComponent.h"
#include "CursorComponent.h"
#include "InputManager.h"
#include "ShipComponent.h"
#include "Eventbus.h"
#include "GameEventClasses.h"

void PlayerManager::update(const float deltaTimeSeconds)
{
	// handle keyinput
	if (m_firstActivePlayer)
	{
		activateFirstPlayer();
		Eventbus::getInstance().fireEvent(new ToggleLabelTextEvent(true, *m_activePlayer));
		m_firstActivePlayer = false;
	}

	if (m_firstActiveUnit)
	{
		activateFirstUnit();
		m_firstActiveUnit = false;
	}

	updateUnit(deltaTimeSeconds);

	if ((*m_activeUnit)->isMoving())
		return;

	if (InputManager::getInstance().isKeyPressed(NEXT_PLAYER_ACTION, *m_activePlayer))
	{
		activateNextPlayer();
	}

	if (InputManager::getInstance().isKeyPressed(NEXT_UNIT_ACTION, *m_activePlayer))
	{
		activateNextUnit();
	}

	updateCursor(deltaTimeSeconds);
}

void PlayerManager::registerCursor(CursorComponent* c)
{
	m_cursor = c;
}

void PlayerManager::updateCursor(const float deltaTimeSeconds)
{
	m_cursor->updateCursor(deltaTimeSeconds);
}

void PlayerManager::updateUnit(const float deltaTimeSeconds)
{
	if (m_units[*m_activePlayer].size() > 0)
	{
		(*m_activeUnit)->updateUnit(deltaTimeSeconds);
		
	}
}

void PlayerManager::registerPlayer(int p)
{
	m_players.push_back(p);
	Eventbus::getInstance().fireEvent(new ToggleLabelTextEvent(false, p));
}

void PlayerManager::registerUnit(int p, SteeringComponent* s)
{
	m_units[p].push_back(s);
	m_ships[p].push_back(getShipFromGameObject(s->getGameObjectPtr()));
}

void PlayerManager::changeActivePlayer()
{
	for (auto ship : m_ships[*m_activePlayer])
		ship->resetMovement();
}

void PlayerManager::activateFirstUnit()
{
	m_activeUnit = m_units[*m_activePlayer].begin();
	m_activeShip = m_ships[*m_activePlayer].begin();

	Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(m_activeShip));
}

void PlayerManager::activateLastUnit()
{
	m_activeUnit = m_units[*m_activePlayer].end()--;
	m_activeShip = m_ships[*m_activePlayer].end()--;

	Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(m_activeShip));
}

void PlayerManager::activateNextUnit()
{
	m_activeUnit++;
	m_activeShip++;

	if (m_activeUnit == m_units[*m_activePlayer].end())
		activateFirstUnit();

	Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(m_activeShip));
}

void PlayerManager::activatePrevUnit()
{
	if (m_activeUnit == m_units[*m_activePlayer].begin())
		activateLastUnit();

	else
	{
		m_activeUnit--;
		m_activeShip--;
	}

	Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(m_activeShip));
}

void PlayerManager::activateFirstPlayer()
{
	m_activePlayer = m_players.begin();
	
	Eventbus::getInstance().fireEvent(new UpdatePlayerStatsEvent());

	activateFirstUnit();
	changeActivePlayer();
}


void PlayerManager::activateLastPlayer()
{
	m_activePlayer = m_players.end()--;

	Eventbus::getInstance().fireEvent(new UpdatePlayerStatsEvent());
	
	activateFirstUnit();
	changeActivePlayer();
}

void PlayerManager::activateNextPlayer()
{
	Eventbus::getInstance().fireEvent(new ToggleLabelTextEvent(false, *m_activePlayer));
	m_activePlayer++;

	if (m_activePlayer == m_players.end())
		activateFirstPlayer();

	Eventbus::getInstance().fireEvent(new ToggleLabelTextEvent(true, *m_activePlayer));
	Eventbus::getInstance().fireEvent(new UpdatePlayerStatsEvent());

	activateFirstUnit();
	changeActivePlayer();
}

void PlayerManager::activatePrevPlayer()
{
	Eventbus::getInstance().fireEvent(new ToggleLabelTextEvent(false, *m_activePlayer));
	if (m_activePlayer == m_players.begin())
		activateLastPlayer();

	else
		m_activePlayer--;

	Eventbus::getInstance().fireEvent(new ToggleLabelTextEvent(true, *m_activePlayer));
	Eventbus::getInstance().fireEvent(new UpdatePlayerStatsEvent());

	activateFirstUnit();
	changeActivePlayer();
}

void PlayerManager::clearComponents()
{
	m_firstActiveUnit = true;
	m_firstActivePlayer = true;

	for (auto player : m_players)
	{
		m_units[player].clear();
		m_ships[player].clear();
	}
	m_units.clear();
	m_ships.clear();
	m_players.clear();
}