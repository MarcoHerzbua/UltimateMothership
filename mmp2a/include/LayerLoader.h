#pragma once

#include "stdafx.h"

class IGameComponent;
class NLTmxMapLayer;
class NLTmxMap;
class GameObject;

using namespace std;
using namespace sf;

class LayerLoader
{
public:
	static vector<NLTmxMapLayer*> loadMapLayers(const NLTmxMap& tilemap);
	static vector<IGameComponent*> createComponentsFromLayers(
		  const vector<NLTmxMapLayer*>& layers
		, GameObject* tilemapObject
		, const map<string, Texture*>& textures
		, const Vector2f& offset
		, NLTmxMap& tilemap);
};