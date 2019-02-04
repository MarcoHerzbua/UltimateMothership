#pragma region include
#pragma once
#include "stdafx.h"
#include "SteeringComponent.h"

class GameObject;
class ControllerComponent;

#pragma endregion

class GUISteeringComponent : public SteeringComponent	
{
public:
	GUISteeringComponent(GameObject * gameObject);
	GUISteeringComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void initTmxData() override;

	void setCurrentNode(Node * node) override;
};