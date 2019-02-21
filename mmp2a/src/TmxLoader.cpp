#include "stdafx.h"
#include "TmxLoader.h"

#include "MapLoader.h"
#include "LayerLoader.h"
#include "TextureLoader.h"
#include "ObjectLoader.h"
#include "NodeGraphLoader.h"

#include "NodeGraphRenderComponent.h"

#include "GameObject.h"

#include "GameObjectManager.h"
#include "RenderManager.h"

void TmxLoader::loadTmxFile(const string& path, const Vector2f& offset)
{
	NLTmxMap* tilemap = MapLoader::loadTileMap(path);

	GameObject* tileMapObject = new GameObject(GameObjects::TILEMAP_OBJECT, Transformation());

	vector<NLTmxMapLayer*> layers = LayerLoader::loadMapLayers(*tilemap);
	map<string, Texture*> textures = TextureLoader::loadTextures(*tilemap);

	tileMapObject->addComponents(LayerLoader::createComponentsFromLayers(layers, tileMapObject, textures, offset, *tilemap));
	
	auto gridLayer = NodeGraphLoader::createNodeGraphComponent(layers, tileMapObject, offset, *tilemap);
	if (gridLayer)
		tileMapObject->addComponent(gridLayer);

	ObjectLoader::loadGameObjects(*tilemap);

	GameObjectManager::getInstance().initTmxData();

	RenderManager::getInstance().sortComponents();

	delete tilemap;
}
