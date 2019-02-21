#include "stdafx.h"
#include "Graph.h"

#include "Node.h"
#include "Edge.h"

Graph::Graph(int rows, int cols)
	: m_rows(rows)
	, m_cols(cols) 
{}

Graph::~Graph()
{
	for (auto n : m_nodes) 
		delete n;
}

void Graph::draw(RenderWindow * window)
{
	for (auto node : m_nodes)
		node->draw(window);
}

Node * Graph::getNodeOnPos(int row, int col)
{
	int oneDIndex = row * m_cols + col;

	if (oneDIndex >= 0 && oneDIndex < m_nodes.size())
		return m_nodes[oneDIndex];

	return 0;
}

Node * Graph::getNodeOnPos(int idx)
{
	if (idx >= 0 && idx < m_nodes.size())
		return m_nodes[idx];

	return 0;
}

stack<InputActions> Graph::getPath(Node& start, Node& destination)
{
	// custom comparison function for set
	auto comp = [](NodeRecord* a, NodeRecord* b) -> bool { return a->estimatedTotalCost < b->estimatedTotalCost; };
	
	list<NodeRecord*> open;
	list<NodeRecord*> closed;

	// heuristic
	auto heuristic = [](Node& a, Node& b) -> float
	{
		Vector2f pos = a.getPosition() - b.getPosition();
		return sqrt(pos.x * pos.x + pos.y * pos.y);
	};

	auto startRecord = new NodeRecord{ &start, nullptr, 0.0f, heuristic(start, destination) };
	open.push_back(startRecord);

	NodeRecord* current = nullptr;
	while (open.size())
	{
		current = *open.begin();
		open.remove(current);

		if (current->node == &destination)
			break;

		for (auto eIti = current->node->getEdgesBeginn(); eIti != current->node->getEdgesEnd(); eIti++)
		{
			auto node2 = (*eIti)->getTargetNode();

			// find node2 in closed and open list
			auto itClosed = find_if(closed.begin(), closed.end(),
				[&node2](NodeRecord* a)->bool
			{ return a->node == node2; });
			auto itOpen = find_if(open.begin(), open.end(),
				[&node2](NodeRecord* a)->bool
			{ return a->node == node2; });

			float endNodeCost = current->costSoFar + (*eIti)->getCost();
			float endNodeHeuristic = 0.0f;
			NodeRecord* node2Record;

			// in closed 
			if (itClosed != closed.end())
			{
				node2Record = *itClosed;
				if (node2Record->costSoFar <= endNodeCost)
					continue;

				closed.remove(node2Record);
				endNodeHeuristic = node2Record->estimatedTotalCost - node2Record->costSoFar;
			}
			else if (itOpen != open.end())
			{
				node2Record = *itOpen;
				if (node2Record->costSoFar <= endNodeCost)
					continue;
				endNodeHeuristic = node2Record->estimatedTotalCost - node2Record->costSoFar;
			}
			else
			{
				node2Record = new NodeRecord{ node2 };
				endNodeHeuristic = heuristic(*node2, destination);
			}

			// update node record
			node2Record->costSoFar = endNodeCost;
			node2Record->connection = current;
			node2Record->estimatedTotalCost = endNodeCost + endNodeHeuristic;

			// reinsert to trigger sort
			if (find(open.begin(), open.end(), node2Record) == open.end())
				open.push_back(node2Record);
			stable_sort(open.begin(), open.end(), comp);
		}

		open.remove(current);
		closed.push_back(current);
	}

	stack<InputActions> path = getpathFromNodeRecord(current, start, destination);

	for (auto n : closed)
		delete n;
	for (auto n : open)
		delete n;

	return path;
}

stack<InputActions> Graph::getpathFromNodeRecord(NodeRecord* rec, const Node& start, const Node& destination)
{
	stack<InputActions> path;

	// trace back to origin
	if (rec->node != &destination)
		return path;
	else
	{
		while (rec->node != &start)
		{
			Node * currNode = rec->node;
			Node * prevNode = rec->connection->node;

			Vector2f traveledDistance = currNode->getPosition() - prevNode->getPosition();

			if (traveledDistance.x > 0.f)
				path.push(MOVE_RIGHT_ACTION);
			if (traveledDistance.x < 0.f)
				path.push(MOVE_LEFT_ACTION);
			if (traveledDistance.y > 0.f)
				path.push(MOVE_DOWN_ACTION);
			if (traveledDistance.y < 0.f)
				path.push(MOVE_UP_ACTION);

			rec = rec->connection;
		}
	}

	return path;
}

int Graph::calcDistance(Node & start, Node & destination)
{
	Vector2i startPos = getNodePosition(&start);
	Vector2i destinationPos = getNodePosition(&destination);

	int distance = abs(startPos.x - destinationPos.x) + abs(startPos.y - destinationPos.y);

	return distance;
}

Vector2i Graph::getNodePosition(Node* n)
{
	int index = 0;
	for (auto node : m_nodes)
	{
		if (node == n)
			break;

		index++;
	}

	Vector2i pos;

	pos.x = index / m_cols;
	pos.y = index % m_cols;

	return pos;

}
