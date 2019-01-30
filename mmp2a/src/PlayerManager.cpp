#include "stdafx.h"
#include "PlayerManager.h"

#include "SteeringComponent.h"
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

	if (InputManager::getInstance().isKeyPressed(NEXT_PLAYER_ACTION, *m_activePlayer))
	{
		activateNextPlayer();
	}

	if (InputManager::getInstance().isKeyPressed(NEXT_UNIT_ACTION, *m_activePlayer))
	{
		activateNextUnit();
	}

	updateCursor(deltaTimeSeconds);
	//updateUnit(deltaTimeSeconds);
}

void PlayerManager::registerCursor(SteeringComponent* s)
{
	m_cursor = s;
}

void PlayerManager::updateCursor(const float deltaTimeSeconds)
{
	m_cursor->updateUnit(deltaTimeSeconds);
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

void PlayerManager::activateFirstUnit()
{
	m_activeUnit = m_units[*m_activePlayer].begin();
}

void PlayerManager::activateLastUnit()
{
	m_activeUnit = m_units[*m_activePlayer].end()--;
}

void PlayerManager::activateNextUnit()
{
	m_activeUnit++;

	if (m_activeUnit == m_units[*m_activePlayer].end())
		activateFirstUnit();
}

void PlayerManager::activatePrevUnit()
{
	if (m_activeUnit == m_units[*m_activePlayer].begin())
		activateLastUnit();

	else
		m_activeUnit--;
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