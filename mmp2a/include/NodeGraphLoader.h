#pragma once

#include "stdafx.h"

class NodeGraphRenderComponent;
class NLTmxMapLayer;
class NLTmxMap;
class GameObject;

using namespace std;
using namespace sf;

class NodeGraphLoader
{
public:
	static NodeGraphRenderComponent* createNodeGraphComponent(
		const vector<NLTmxMapLayer*>& layers
		, GameObject* tilemapObject
		, const Vector2f& offset
		, NLTmxMap& tilemap);
};