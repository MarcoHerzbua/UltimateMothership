#pragma region include 

#pragma once
#include "stdafx.h"

#include "Direction.h"
#include "GameObject.h"
#include "Edge.h"

namespace hm {}

#include "HelperMethods.h"

#pragma endregion

using namespace std;
using namespace sf;
using namespace hm;

class Node
{
public:
	~Node(); // TODO rule of three

	void draw(RenderWindow* window);

	void addEdge(Edge* e) { m_edges.push_back(e); };

	Node* getTargetNode(Direction d);
	Edge* getEdgeInDir(Direction d);

	list<Edge*>::iterator getEdgesBeginn() { return m_edges.begin(); };
	list<Edge*>::iterator getEdgesEnd() { return m_edges.end(); };

	Vector2f getPosition() { return m_debugGeometry.getPosition(); };
	void setPosition(Vector2f p) { m_debugGeometry.setPosition(p); };
	void setOrigin(Vector2f o) { m_debugGeometry.setOrigin(o); };
	void setRadius(float r) { m_debugGeometry.setRadius(r); };
	void setFillColor(Color c) { m_debugGeometry.setFillColor(c); };
private:
	CircleShape m_debugGeometry;

	list<Edge*> m_edges;
};