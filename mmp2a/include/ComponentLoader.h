#pragma once

#include "stdafx.h"
#include "GameComponents.h"
#include "NLTmxMap.h"
#include "GameObject.h"

class IGameComponent;

using namespace std;
using namespace sf;

class ComponentLoader
{
public:
	static vector<IGameComponent*> loadComponents(const NLTmxMapObjectGroup& group, GameObject* gameObject);
	static IGameComponent* createComponent(const GameComponents id, NLTmxMapObject& mapObject, GameObject* gameObject); 
};