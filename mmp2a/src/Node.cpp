#include "stdafx.h"
#include "Node.h"

Node::~Node()
{
	for (auto e : m_edges) 
		delete e;
}

void Node::draw(RenderWindow * window)
{
	window->draw(m_debugGeometry);
	for (auto edge : m_edges)
		edge->draw(window);
}

Node * Node::getTargetNode(Direction d)
{
	Edge* e = getEdgeInDir(d);

	if (e)
		return e->getTargetNode();

	return nullptr;
}

Edge * Node::getEdgeInDir(Direction d)
{
	for (auto e : m_edges)
	{
		if (directionToVec2f(d) == normalizeVec2f(calcDistVec(*this, *(e->getTargetNode()))))
			return e;
	}

	return nullptr;
}
