#pragma region include

#pragma once
#include "stdafx.h"

#include "IControllerComponent.h"

#include "InputComponents.h"

class IInputComponent;

#pragma endregion

class ControllerComponent : public IControllerComponent
{
public:
	ControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	ControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	virtual ~ControllerComponent() = default;

	virtual void update(const float deltaTimeSeconds) override;
	virtual void exit() override;

	virtual void initTmxData() override = 0;

	void registerInput(IInputComponent* c);
	void removeInput(InputComponents cId);
	IInputComponent* findInput(InputComponents cId);
	vector<IInputComponent*>::iterator findInputIterator(const InputComponents cId);

	virtual void activate() = 0;

protected:
	vector<IInputComponent *> m_inputs;
};