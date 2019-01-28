#include "stdafx.h"
#include "NodeGraphLoader.h"

NodeGraphRenderComponent * NodeGraphLoader::createNodeGraphComponent(const vector<NLTmxMapLayer*>& layers
	, GameObject * tilemapObject
	, const Vector2f & offset
	, NLTmxMap & tilemap)
{
	NLTmxMapLayer* gridLayer = nullptr;

	for (auto layer : layers)
	{
		for (auto prop : layer->properties)
			if (prop->name == "layerId")
				if (prop->value == "nodeGrid")
				{
					gridLayer = layer;
					break;
				}

		if (gridLayer) break;
	}
	
	if (gridLayer)
	{
		NodeGraphRenderComponent* graphCmp = new NodeGraphRenderComponent(tilemapObject, *gridLayer);
		graphCmp->init(tilemap, offset);
		return graphCmp;
	}

	return nullptr;
}
