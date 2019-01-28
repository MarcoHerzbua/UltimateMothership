#pragma region include 

#pragma once
#include "stdafx.h"

#include "Node.h"
#include "InputActions.h"

#pragma endregion

using namespace std;
using namespace sf;

struct NodeRecord
{
	Node* node;
	NodeRecord* connection; //< how was this node reached
	float costSoFar;
	float estimatedTotalCost;
};

class Graph
{
public:
	Graph() = default;
	Graph(int rows, int cols);

	~Graph(); //TODO rule of three

	void draw(RenderWindow* window);

	void addNode(Node* n) { m_nodes.push_back(n); };

	stack<InputActions> getPath(Node& start, Node& destination);
	stack<InputActions> getpathFromNodeRecord(NodeRecord* rec, const Node& start, const Node& destination);

	vector<Node*>::iterator getNodesBeginn() { return m_nodes.begin(); };
	vector<Node*>::iterator getNodesEnd() { return m_nodes.end(); };

	Node* getNodeOnPos(int row, int col);
	Node* getNodeOnPos(int idx);

	int getRows() { return m_rows; };
	int getCols() { return m_cols; };

private:
	vector<Node*> m_nodes;

	int m_rows;
	int m_cols;
};