#include "stdafx.h"
#include "MapLoader.h"

#include "NLTmxMap.h"
#include "GameObjectManager.h"

NLTmxMap * MapLoader::loadTileMap(const string & filename)
{
	FileInputStream mapStream;
	if (!mapStream.open(GameObjectManager::getInstance().getAssetPath() + filename))
	{
		err() << "loadMap: could not open file " << filename << endl;
		return nullptr;
	}

	// convert FileInputStream to char* mapBuffer
	char * mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	// now lets load a NLTmxMap
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;

	err() << "Load tilemap with size: " << tilemap->width << ", "
		<< tilemap->height << " and tilesize: " << tilemap->tileWidth
		<< ", " << tilemap->tileHeight << std::endl;

	return tilemap;
}
