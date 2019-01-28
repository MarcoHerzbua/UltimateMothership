#pragma once

#include "stdafx.h"
#include "GameObjects.h"
#include "NLTmxMap.h"

class GameObject;

using namespace std;
using namespace sf;

class ObjectLoader
{
public:
	static vector<GameObject*> loadGameObjects(const NLTmxMap& tilemap);
	static GameObject* createGameObject(const GameObjects id, const NLTmxMapObjectGroup& group);
};