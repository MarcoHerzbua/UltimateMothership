#include "stdafx.h"
#include "LayerLoader.h"

#include "GameObject.h"
#include "IGameComponent.h"
#include "NLTmxMap.h"

#include "LayerRenderComponent.h"

vector<NLTmxMapLayer*> LayerLoader::loadMapLayers(const NLTmxMap& tilemap)
{
	vector<NLTmxMapLayer*> layers;

	for (int layerIdx = 0; layerIdx < (int)tilemap.layers.size(); layerIdx++)
	{
		NLTmxMapLayer* layer = tilemap.layers[layerIdx];

		layers.push_back(layer);
	}

	return layers;
}

vector<IGameComponent*> LayerLoader::createComponentsFromLayers(
	  const vector<NLTmxMapLayer*>& layers
	, GameObject* tilemapObject
	, const map<string, Texture*>& textures
	, const Vector2f& offset
	, NLTmxMap& tilemap)
{
	vector<IGameComponent*> componentLayers;

	for (auto layer : layers)
	{
		LayerRenderComponent* layerComponent = new LayerRenderComponent(tilemapObject, *layer);
		layerComponent->init(tilemap, textures, offset);

		componentLayers.push_back(static_cast<IGameComponent*>(layerComponent));
	}
	
	return componentLayers;
}
