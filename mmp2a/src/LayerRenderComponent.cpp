#pragma region include

#include "stdafx.h"
#include "LayerRenderComponent.h"
#include "RenderManager.h"
#include "Game.h"
#include "SpriteRenderComponent.h"

#pragma endregion

LayerRenderComponent::LayerRenderComponent(GameObject * gameObject)
{
	m_gameObject = gameObject;
	m_mapObject = nullptr;
	m_mapLayer = nullptr;
	m_id = LAYER_RENDER_COMPONENT;
	RenderManager::getInstance().addComponent(this);
}

LayerRenderComponent::LayerRenderComponent(GameObject * gameObject, NLTmxMapLayer & mapLayer)
{
	m_gameObject = gameObject;
	m_mapObject = nullptr;
	m_mapLayer = &mapLayer;
	m_id = LAYER_RENDER_COMPONENT;
	RenderManager::getInstance().addComponent(this);
}

void LayerRenderComponent::update(const float deltaTime)
{

}

void LayerRenderComponent::draw(sf::RenderWindow* window)
{
	for (auto sprite : m_sprites)
	{
		window->draw(*sprite);
	}
}

void LayerRenderComponent::exit()
{
	RenderComponent::exit();

	for (auto &sprite : m_sprites)
	{
		delete sprite;
	}
	m_sprites.clear();
}

void LayerRenderComponent::setScale(const float scale)
{

}


void LayerRenderComponent::init(NLTmxMap& tilemap, const map<string, Texture *>& textures, const sf::Vector2f& offset)
{
	//set pointer to textures saved in the GameState
	int size = m_mapLayer->width * m_mapLayer->height;

	// go over all elements in the layer
	for (int i = 0; i < size; i++)
	{
		int grid = m_mapLayer->data[i];

		if (grid == 0)				
			continue;

		// get tileset and tileset texture
		NLTmxMapTileset* tileset = tilemap.getTilesetForGrid(grid);
		Vector2i tileSize(tilemap.tileWidth, tilemap.tileHeight);
		Texture* texture = textures.at(tileset->name);

		// horizontal tile count in tileset texture
		int tileCountX = (*texture).getSize().x / tileSize.x;

		// calcualte position of tile
		sf::Vector2f position;
		position.x = (i % m_mapLayer->width) * (float)tileSize.x;
		position.y = (i / m_mapLayer->width) * (float)tileSize.y;
		position += offset;

		// calculate 2d idx of tile in tileset texture
		int idx = grid - tileset->firstGid;
		int idxX = idx % tileCountX;
		int idxY = idx / tileCountX;

		// calculate source area of tile in tileset texture
		IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

		Sprite * sprite = new Sprite(*texture, source); // = std::make_shared<sf::Sprite>(texture, source);

		sprite->setPosition(position);

		m_sprites.push_back(sprite);

	}

}

void LayerRenderComponent::initTmxData()
{
	if (!m_mapLayer)
		return;

	m_zIndex = 0;
	m_layerId = NULL_LAYER;

	for (auto prop : m_mapLayer->properties)
	{
		if (prop->name == "zIndex")
			m_zIndex = stoi(prop->value);
		if (prop->name == "layerId")
			m_layerId = stringToLayerComponents(prop->value);
	}

	m_mapLayer = nullptr;
	m_mapObject = nullptr;
}
