#include "stdafx.h"
#include "NodeGraphRenderComponent.h"

#include "GameObjectManager.h"
#include "Game.h"
#include "RenderManager.h"

NodeGraphRenderComponent::NodeGraphRenderComponent(GameObject * gameObject)
{
	m_gameObject = gameObject;
	m_mapObject = nullptr;
	m_mapLayer = nullptr;
	m_id = NODE_GRAPH_RENDER_COMPONENT;
	RenderManager::getInstance().addComponent(this);
}

NodeGraphRenderComponent::NodeGraphRenderComponent(GameObject * gameObject, NLTmxMapLayer& mapLayer)
{
	m_gameObject = gameObject;
	m_mapObject = nullptr;
	m_mapLayer = &mapLayer;
	m_id = NODE_GRAPH_RENDER_COMPONENT;
	RenderManager::getInstance().addComponent(this);
}

void NodeGraphRenderComponent::update(const float deltaTimeSeconds)
{
}

void NodeGraphRenderComponent::exit()
{
	RenderComponent::exit();
	delete m_graph;
}

void NodeGraphRenderComponent::setScale(const float scale)
{
}

void NodeGraphRenderComponent::init(NLTmxMap& tilemap, const Vector2f& offset)
{
	m_mapObjectInfo = MapObjectInfo(tilemap.width, tilemap.height, tilemap.tileWidth, tilemap.tileHeight, offset);
}

void NodeGraphRenderComponent::initTmxData()
{
	if (!m_mapLayer)
		return;

	m_zIndex = 9;

	int cols = m_mapObjectInfo.m_width;
	int rows = m_mapObjectInfo.m_height;

	for (auto prop : m_mapLayer->properties)
	{
		if (prop->name == "zIndex")
			m_zIndex = stoi(prop->value);
		if (prop->name == "rows")
			rows = stoi(prop->value);
		if (prop->name == "cols")
			cols = stoi(prop->value);
	}

	createGrid(rows, cols);
	
	m_mapLayer = nullptr;
	m_mapObject = nullptr;
}

void NodeGraphRenderComponent::createGrid(int rows, int cols)
{
	m_graph = new Graph(rows, cols);

	int endX = m_mapObjectInfo.m_width;
	int endY = m_mapObjectInfo.m_height;

	float startX = 0;
	float startY = 0;

	float incX = (endX - startX) / (float)cols;
	float incY = (endY - startY) / (float)rows;

	startX = incX / 2.f;
	startY = incY / 2.f;

	float radius = 5.f;

	for (float y = startY; y < endY; y += incY)
		for (float x = startX; x < endX; x += incX)
		{
			Vector2i tileSize(m_mapObjectInfo.m_tileWidth, m_mapObjectInfo.m_tileHeight);

			// calcualte position of tile
			Vector2f position;
			position.x = x * (float)tileSize.x;
			position.y = y * (float)tileSize.y;
			position += m_mapObjectInfo.m_offset;

			Node* node = new Node{};

			node->setOrigin(Vector2f(radius, radius));
			node->setPosition(position);
			node->setRadius(radius);
			node->setFillColor(Color(255, 255, 255, 50));

			m_graph->addNode(node);
		}

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
		{
			int idx = y * cols + x;
			Node* node = m_graph->getNodeOnPos(idx);

			if (x < cols - 1)
			{
				int idxRight = idx + 1;
				Node* nodeR = m_graph->getNodeOnPos(idxRight);
				node->addEdge(new Edge( calcNodeDistance(*node, *nodeR), nodeR ));
			}

			if (y < rows - 1)
			{
				int idxBottom = (y + 1)*cols + x;
				Node* nodeB = m_graph->getNodeOnPos(idxBottom);
				node->addEdge(new Edge( calcNodeDistance(*node, *nodeB), nodeB ));
			}

			if (x >= 1)
			{
				int idxLeft = idx - 1;
				Node* nodeL = m_graph->getNodeOnPos(idxLeft);
				node->addEdge(new Edge( calcNodeDistance(*node, *nodeL), nodeL ));
			}
			if (y >= 1)
			{
				int idxTop = (y - 1)*cols + x;
				Node* nodeT = m_graph->getNodeOnPos(idxTop);
				node->addEdge(new Edge( calcNodeDistance(*node, *nodeT), nodeT ));
			}


		}

	for (auto nIti = m_graph->getNodesBegin(); nIti != m_graph->getNodesEnd(); nIti++)
		for (auto eIti = (*nIti)->getEdgesBeginn(); eIti != (*nIti)->getEdgesEnd(); eIti++)
		{
			Vector2f n2_min_n = 0.5f * ((*eIti)->getTargetNode()->getPosition() - (*nIti)->getPosition());
			Vector2f pos = (*nIti)->getPosition() + n2_min_n;
			Vector2f size;
			size.x = radius * 0.5f + abs(n2_min_n.x) * 0.5f;
			size.y = radius * 0.5f + abs(n2_min_n.y) * 0.5f;
			(*eIti)->setSize(size);
			(*eIti)->setOrigin(size * 0.5f);
			(*eIti)->setFillColor(Color(255, 255, 255, 50));
			(*eIti)->setPosition(pos);
		}
}

void NodeGraphRenderComponent::draw(RenderWindow* window)
{
	m_graph->draw(window);
}
