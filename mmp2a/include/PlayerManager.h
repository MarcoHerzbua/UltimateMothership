#pragma region include

#pragma once
#include "stdafx.h"

#include "HelperMethods.h"

class SteeringComponent;
class ShipComponent;
class CursorComponent;

using namespace sf;
using namespace hm;
using namespace std;

#pragma endregion


class PlayerManager
{
public:
	static PlayerManager& getInstance();

	void update(const float deltaTimeSeconds);
	void updateUnit(const float deltaTimeSeconds);
	void updateCursor(const float deltaTimeSeconds);

	void registerPlayer(int p);
	void registerUnit(int p, SteeringComponent* s);
	void registerCursor(CursorComponent* c);

	void changeActivePlayer();
	void preChangeActiveUnit();
	void changeActiveUnit();

	void activateFirstUnit();
	void activateLastUnit();

	void activateNextUnit();
	void activatePrevUnit();

	void activateFirstPlayer();
	void activateLastPlayer();

	void activateNextPlayer();
	void activatePrevPlayer();

	void clearComponents();

	int getRessources(int playerIndex) { return m_ressources[playerIndex]; };

	void increaseRessources(int playerIndex) { m_ressources[playerIndex]++; };
	void increaseRessources(int playerIndex, int amount) { m_ressources[playerIndex] += amount; };
	void decreaseRessources(int playerIndex, int amount) { m_ressources[playerIndex] -= amount; };

	int getActivePlayer() { return *m_activePlayer; };
	SteeringComponent* getActiveUnit() { return *m_activeUnit; };
	ShipComponent* getActiveShip() { return *m_activeShip; };
	CursorComponent* getCursor() { return m_cursor; };

private:
	PlayerManager(void) = default;
	~PlayerManager(void) = default;
	PlayerManager(const PlayerManager& p) = delete;
	PlayerManager& operator=(PlayerManager const&) = delete;

	vector<int> m_players;
	map<int, vector<SteeringComponent*>> m_units;
	map<int, vector<ShipComponent*>> m_ships;
	map<int, int> m_ressources;

	CursorComponent* m_cursor;

	vector<int>::iterator m_activePlayer;
	vector<SteeringComponent*>::iterator m_activeUnit;
	vector<ShipComponent*>::iterator m_activeShip;

	bool m_firstActivePlayer = true;
	bool m_firstActiveUnit = true;
};

inline PlayerManager& PlayerManager::getInstance()
{
	static PlayerManager m_instance;
	return m_instance;
}
