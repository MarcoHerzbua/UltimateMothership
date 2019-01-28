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

class HumanInputComponent : public IInputComponent
{
public:
	HumanInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent);
	HumanInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent, NLTmxMapObject& mapObject);

	virtual void update(const float deltaTimeSeconds) override;
	virtual void exit() override;

	virtual void init(InputActions action);
	virtual void initTmxData() override;

private:
	function<void(float)> m_doAction;
	
	SteeringComponent* m_steeringComp;

	virtual function<void(float)> generateFunction(InputActions action);
};