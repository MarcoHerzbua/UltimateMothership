#pragma once

#include "stdafx.h"

#include "GameComponents.h"

class IGameComponent;
class GameObject;
class NLTmxMapObjectGroup;
class NLTmxMapObject;

using namespace std;
using namespace sf;

class ComponentLoader
{
public:
	static vector<IGameComponent*> loadComponents(const NLTmxMapObjectGroup& group, GameObject* gameObject);
	static IGameComponent* createComponent(const GameComponents id, NLTmxMapObject& mapObject, GameObject* gameObject); 
};