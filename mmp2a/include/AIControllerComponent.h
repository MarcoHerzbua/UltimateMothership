#pragma region include

#pragma once
#include "stdafx.h"
#include "NodeGraphRenderComponent.h"

#include "ControllerComponent.h"


class GameObject;
class SteeringComponent;

#pragma endregion

class AIControllerComponent : public ControllerComponent
{
public:
	AIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	AIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	void init(Graph* graph);
	void initTmxData() override;

	void activate() override;

	InputActions getNextActionFromStack();
private:
	Graph* m_graph;
	stack<InputActions> m_aiActionStack;
};