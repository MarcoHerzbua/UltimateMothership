#pragma region include

#pragma once
#include "stdafx.h"

#include "IInputComponent.h"

#include "InputActions.h"
#include "NLTmxMap.h"

class GameObject;
class SteeringComponent;

using namespace std;
using namespace sf;

#pragma endregion

class AiInputComponent : public IInputComponent
{
public:
	AiInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent);
	AiInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void init();
	void initTmxData() override;

private:
	function<void(float, InputActions*)> m_doAction;
	InputActions m_action;
	
	SteeringComponent* m_steeringComp;

	function<void(float, InputActions*)> generateFunction();
};