#pragma region include

#pragma once
#include "stdafx.h"

#include "ControllerComponent.h"

using namespace std;
using namespace sf;
#pragma endregion

class HumanControllerComponent : public ControllerComponent
{
public:
	HumanControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	HumanControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	void initTmxData() override;

	void activate() override;
};