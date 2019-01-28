#pragma once

#include "stdafx.h"
#include "NodeGraphRenderComponent.h"

class NodeGraphLoader
{
public:
	static NodeGraphRenderComponent* createNodeGraphComponent(
		const vector<NLTmxMapLayer*>& layers
		, GameObject* tilemapObject
		, const Vector2f& offset
		, NLTmxMap& tilemap);
};