#pragma region include

#pragma once
#include "stdafx.h"
#include "NLTmxMap.h"

#include "GameComponents.h"
#include "Stats.h"

class GameObject;

using namespace std;
using namespace sf;

#pragma endregion

class ShipManager
{
public:
	static ShipManager& getInstance();

	//
	// void update(const float deltaTimeSeconds);
	//
	// void initTmxData();

	void exit();

	void registerShip(GameObject* ship);

	void registerShipType(GameComponents id, Stats baseStats);
	GameObject* createShip(GameComponents id, int playerIndex);


private:
	ShipManager(void) = default;
	~ShipManager(void) = default;
	ShipManager(const ShipManager& p) = delete;
	ShipManager& operator=(ShipManager const&) = delete;

	vector<GameObject*> m_ships;
};

inline ShipManager& ShipManager::getInstance()
{
	static ShipManager m_instance;
	return m_instance;
}