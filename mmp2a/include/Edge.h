#pragma region include 

#pragma once
#include "stdafx.h"

class Node;

using namespace std;
using namespace sf;

#pragma endregion


class Edge
{
public:
	Edge() = default;
	Edge(float cost, Node* node2);

	void draw(RenderWindow* window);


	Node* getTargetNode() { return m_node2; };
	float getCost() { return m_cost; };

	Vector2f getPosition() { return m_debugGeometry.getPosition(); };
	void setPosition(Vector2f p) { m_debugGeometry.setPosition(p); };
	void setOrigin(Vector2f o) { m_debugGeometry.setOrigin(o); };
	void setFillColor(Color c) { m_debugGeometry.setFillColor(c); };
	void setSize(Vector2f s) { m_debugGeometry.setSize(s); };

private:
	float m_cost;
	Node* m_node2;

	RectangleShape m_debugGeometry;
};