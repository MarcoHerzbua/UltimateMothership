#pragma region include

#pragma once
#include "stdafx.h"
#include "NodeGraphRenderComponent.h"

#include "ControllerComponent.h"

class GameObject;
class SteeringComponent;

#pragma endregion

class HumanControllerComponent : public ControllerComponent
{
public:
	HumanControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	HumanControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	void initTmxData() override;

	void activate() override;
};