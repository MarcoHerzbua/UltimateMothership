#include "stdafx.h"
#include "Edge.h"

#include "Node.h"

Edge::Edge(float cost, Node * node2)
	: m_cost(cost)
	, m_node2(node2)
{}

void Edge::draw(RenderWindow * window)
{
	window->draw(m_debugGeometry);
}
