#include "stdafx.h"
#include "PlayerManager.h"

#include "SteeringComponent.h"
#include "CursorComponent.h"
#include "InputManager.h"

void PlayerManager::update(const float deltaTimeSeconds)
{
	// handle keyinput
	if (m_firstActivePlayer)
	{
		activateFirstPlayer();
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
		(*m_activeUnit)->updateUnit(deltaTimeSeconds);
}

void PlayerManager::registerPlayer(int p)
{
	m_players.push_back(p);
}

void PlayerManager::registerUnit(int p, SteeringComponent* s)
{
	m_units[p].push_back(s);
}

void PlayerManager::changeActiveShip()
{
	m_activeShip = getShipFromGameObject((*m_activeUnit)->getGameObjectPtr());
}

void PlayerManager::activateFirstUnit()
{
	m_activeUnit = m_units[*m_activePlayer].begin();
	changeActiveShip();
}

void PlayerManager::activateLastUnit()
{
	m_activeUnit = m_units[*m_activePlayer].end()--;
	changeActiveShip();
}

void PlayerManager::activateNextUnit()
{
	m_activeUnit++;

	if (m_activeUnit == m_units[*m_activePlayer].end())
		activateFirstUnit();

	changeActiveShip();
}

void PlayerManager::activatePrevUnit()
{
	if (m_activeUnit == m_units[*m_activePlayer].begin())
		activateLastUnit();

	else
		m_activeUnit--;

	changeActiveShip();
}

void PlayerManager::activateFirstPlayer()
{
	m_activePlayer = m_players.begin();
	
	activateFirstUnit();
}


void PlayerManager::activateLastPlayer()
{
	m_activePlayer = m_players.end()--;
	
	activateFirstUnit();
}

void PlayerManager::activateNextPlayer()
{
	m_activePlayer++;

	if (m_activePlayer == m_players.end())
		activateFirstPlayer();

	activateFirstUnit();
}

void PlayerManager::activatePrevPlayer()
{
	if (m_activePlayer == m_players.begin())
		activateLastPlayer();

	else
		m_activePlayer--;

	activateFirstUnit();
}

void PlayerManager::clearComponents()
{
	m_firstActiveUnit = true;
	m_firstActivePlayer = true;

	for (auto player : m_players)
	{
		m_units[player].clear();
	}
	m_units.clear();
	m_players.clear();
}