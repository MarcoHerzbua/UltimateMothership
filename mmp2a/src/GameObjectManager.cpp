#pragma region include

#include "stdafx.h"
#include "GameObjectManager.h"
#include "RenderManager.h"

// game classes
#include "Game.h"
#include "GameObject.h"

//enums
#include "GameComponents.h"



#pragma endregion


void GameObjectManager::init(Game* game)
{
	m_game = game;
}


void GameObjectManager::update(const float deltaTimeSeconds)
{
	for (auto obj : m_objects)
		obj->update(deltaTimeSeconds);
}

void GameObjectManager::initTmxData()
{
	for (auto object : m_objects)
	{
		object->initTmxData();
	}
}


void GameObjectManager::registerGameObject(GameObject * o)
{
	m_objects.push_back(o);
}

void GameObjectManager::registerGameObjects(vector<GameObject*> ov)
{
	for (auto o : ov)
		m_objects.push_back(o);
}

void GameObjectManager::removeGameObject(GameObject* o)
{
	auto oIti = findFirstGameObjectIterator(o);
	if (oIti != m_objects.end())
	{
		m_objects.erase(oIti);

		(*oIti)->exit();
		delete *oIti;
	}
}

void GameObjectManager::removeGameObjects(const GameObjects oId)
{
	auto oIti = findFirstGameObjectIterator(oId);
	while (oIti != m_objects.end())
	{
		m_objects.erase(oIti);

		(*oIti)->exit();
		delete *oIti;

		oIti = findFirstGameObjectIterator(oId);
	}
}

void GameObjectManager::clearGameObjects()
{
	for (auto o : m_objects)
	{
		o->exit();
		delete o;
	}

	m_objects.clear();
}

vector<GameObject*> GameObjectManager::findGameObjects(const GameObjects oId)
{
	vector<GameObject*> gameObjects;

	for (auto o : m_objects)
	{
		if (o->getId() == oId)
			gameObjects.push_back(o);
	}

	return gameObjects;
}

vector<GameObject*>::iterator GameObjectManager::findFirstGameObjectIterator(const GameObjects oId)
{
	for (auto oIti = m_objects.begin(); oIti != m_objects.end(); oIti++)
	{
		if ((*oIti)->getId() == oId) return oIti;
	}

	return m_objects.end();
}

vector<GameObject*>::iterator GameObjectManager::findFirstGameObjectIterator(GameObject* o)
{
	for (auto oIti = m_objects.begin(); oIti != m_objects.end(); oIti++)
	{
		if ((*oIti) == o) return oIti;
	}
	return m_objects.end();
}


void GameObjectManager::exit()
{
	clearGameObjects();
}

Game* GameObjectManager::getGamePtr()
{
	return m_game;
}

const string GameObjectManager::getAssetPath()
{
	return m_assetPath;
}

GameObjectManager& GameObjectManager::getInstance() {
	static GameObjectManager m_instance;
	return m_instance;
}



