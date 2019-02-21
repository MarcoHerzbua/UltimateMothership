#pragma region include

#pragma once
#include "stdafx.h"
#include "RenderComponent.h"

#include "HelperMethods.h"

class Node;
class Graph;
class NLTmxMapLayer;
class NLTmxMap;

using namespace sf;
using namespace std;
using namespace hm;
#pragma endregion

struct MapObjectInfo
{
	MapObjectInfo() = default;
	MapObjectInfo(int width, int height, int tileWidth, int tileHeight, const sf::Vector2f offset)
		: m_width(width)
		, m_height(height)
		, m_tileWidth(tileWidth)
		, m_tileHeight(tileHeight)
		, m_offset(offset) {}

	int m_width;
	int m_height;
	int m_tileWidth;
	int m_tileHeight;
	sf::Vector2f m_offset;
};

class NodeGraphRenderComponent : public RenderComponent
{
public:
	NodeGraphRenderComponent(GameObject* gameObject);
	NodeGraphRenderComponent(GameObject* gameObject, NLTmxMapLayer& mapLayer);

	void update(const float deltaTime) override;
	void draw(RenderWindow* window) override;
	void exit() override;
	void setScale(const float scale) override;

	void init(NLTmxMap& tilemap, const sf::Vector2f& offset);
	void initTmxData() override;

	Graph & getGraph() { return *m_graph; }
private:
	Graph * m_graph;
	NLTmxMapLayer* m_mapLayer;
	MapObjectInfo m_mapObjectInfo;

	void createGrid(int rows, int cols);
};
