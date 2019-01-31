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

GameObject * Node::getGameObject(GameObjects go)
{
	for (auto *object : m_gameObjects)
	{
		if (object->getId() == go)
			return object;
	}
	err() << "Gameobject in not found in Node\n";
	return nullptr;
}

void Node::addGameObject(GameObject * go)
{
	m_gameObjects.push_back(go);
}

bool Node::removeGameObject(GameObjects go)
{
	auto objectPtr = getGameObject(go);
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it) == objectPtr)
		{
			m_gameObjects.erase(it);
			return true;
		}
	}
	return false;
}

bool Node::removeGameObject(GameObject * go)
{
	if (m_gameObjects.size() == 0)
		return false;

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if ((*it) == go)
		{
			m_gameObjects.erase(it);
			return true;
		}
	}
	return false;

}
