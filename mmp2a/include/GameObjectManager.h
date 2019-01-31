#pragma region include

#pragma once
#include "stdafx.h"
#include "NLTmxMap.h"

// enums
#include "GameObjects.h"
#include "GameComponents.h"

// forward declaration
class Game;
class GameObject;
class IGameComponent;

using namespace std;
using namespace sf;

#pragma endregion

class GameObjectManager
{
public:
	static GameObjectManager& getInstance();

	void init(Game * game);

	void update(const float deltaTimeSeconds);

	void initTmxData();

	void registerGameObject(GameObject* o);
	void registerGameObjects(vector<GameObject*> ov);
	void removeGameObject(GameObject* o);
	void removeGameObjects(const GameObjects oId);
	void clearGameObjects();
	vector<GameObject*> findGameObjects(const GameObjects oId);
	vector<GameObject*>::iterator findFirstGameObjectIterator(const GameObjects oId);
	vector<GameObject*>::iterator findFirstGameObjectIterator(GameObject* o);

	void markForDelete(GameObject* o);
	
	void exit();

	Game * getGamePtr();

	const string getAssetPath();
private:
	GameObjectManager(void) = default;
	~GameObjectManager(void) = default;
	GameObjectManager(const GameObjectManager& p) = delete;
	GameObjectManager& operator=(GameObjectManager const&) = delete;


	Game * m_game;

	vector<GameObject*> m_objects;
	vector<GameObject*> m_markedForDelete;

	const string m_assetPath = "../spaceAssets/";

	bool m_firstRegister = true;
}; 
