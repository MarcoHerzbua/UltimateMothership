#pragma region include
#pragma once
#include "stdafx.h"
#include "ControllerComponent.h"

using namespace std;
using namespace sf;
#pragma endregion


class GUIControllerComponent : public ControllerComponent
{
public:
	GUIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	GUIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	void initTmxData() override;

	void activate() override;
};