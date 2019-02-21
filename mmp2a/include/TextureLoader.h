#pragma once
#include "stdafx.h"

class NLTmxMap;

using namespace std;
using namespace sf;

class TextureLoader
{
public:
	static map<string, Texture*> loadTextures(const NLTmxMap& tilemap);
};