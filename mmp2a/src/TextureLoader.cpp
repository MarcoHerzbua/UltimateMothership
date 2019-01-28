#include "stdafx.h"
#include "TextureLoader.h"

map<string, Texture*> TextureLoader::loadTextures(const NLTmxMap& tilemap)
{
	map<string, Texture*> textures;

	for (auto tileset : tilemap.tilesets)
	{
		sf::err() << "Load tileset: " << tileset->name << " width filename: "
			<< tileset->filename << " and tilesize: " << tileset->tileWidth
			<< ", " << tileset->tileHeight << std::endl;

		sf::Texture * texture = new Texture();
		string assetPath = GameObjectManager::getInstance().getAssetPath();

		if (!texture->loadFromFile(assetPath + tileset->filename))
			sf::err() << "Could not load texture " << assetPath + tileset->filename << endl;
		
		textures[tileset->name] = texture;
	}

	return textures;
}
