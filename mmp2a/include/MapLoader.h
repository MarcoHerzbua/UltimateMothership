#pragma once
#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "NLTmxMap.h"

#include "GameObjectManager.h"

using namespace std;
using namespace sf;

class MapLoader
{
public:
	static NLTmxMap* loadTileMap(const string & filename);
};