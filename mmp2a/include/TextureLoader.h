#pragma once
#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "NLTmxMap.h"

#include "GameObjectManager.h"

using namespace std;
using namespace sf;

class TextureLoader
{
public:
	static map<string, Texture*> loadTextures(const NLTmxMap& tilemap);
};