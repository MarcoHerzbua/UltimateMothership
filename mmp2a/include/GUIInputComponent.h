#pragma region include
#pragma once
#include "stdafx.h"

#include "HumanInputComponent.h"
#pragma endregion

class GUIInputComponent : public HumanInputComponent
{
public:
	GUIInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent);
	GUIInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void init(InputActions action) override;
	void initTmxData() override;
	void exit() override;
private:
	function<void(float)> m_doAction;

	SteeringComponent* m_steeringComp;

	function<void(float)> generateFunction(InputActions action) override;
};