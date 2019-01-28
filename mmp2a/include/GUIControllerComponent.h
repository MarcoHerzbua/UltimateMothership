#pragma region include
#pragma once
#include "stdafx.h"
#include "ControllerComponent.h"
#include "IGameComponent.h"
#include "IInputComponent.h"
#include "InputComponents.h"
#include "GUIInputComponent.h"
class GameObject;

#pragma endregion


class GUIControllerComponent
	: public ControllerComponent
{
public:
	GUIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	GUIControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	void initTmxData() override;

	void activate() override;
};