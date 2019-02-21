#pragma region include

#pragma once
#include "stdafx.h"

#include "ControllerComponent.h"

#include "InputActions.h"

class Node;
class Graph;

#pragma endregion

class AIControllerComponent : public ControllerComponent
{
public:
	AIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	AIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	void init(Graph* graph);
	void initTmxData() override;

	void activate() override;
	void moveToTargetNode(Node* n);

	bool isMoving() { return m_aiActionStack.size() != 0; };

	InputActions getNextActionFromStack();
private:
	Graph* m_graph;
	stack<InputActions> m_aiActionStack;
};