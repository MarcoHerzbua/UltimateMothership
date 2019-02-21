#pragma once
#include "stdafx.h"

class NLTmxMap;

using namespace std;
using namespace sf;

class MapLoader
{
public:
	static NLTmxMap* loadTileMap(const string & filename);
};